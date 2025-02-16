/***************************************************************************
 * Copyright (C) gempa GmbH                                                *
 * All rights reserved.                                                    *
 * Contact: gempa GmbH (seiscomp-dev@gempa.de)                             *
 *                                                                         *
 * GNU Affero General Public License Usage                                 *
 * This file may be used under the terms of the GNU Affero                 *
 * Public License version 3.0 as published by the Free Software Foundation *
 * and appearing in the file LICENSE included in the packaging of this     *
 * file. Please review the following information to ensure the GNU Affero  *
 * Public License version 3.0 requirements will be met:                    *
 * https://www.gnu.org/licenses/agpl-3.0.html.                             *
 *                                                                         *
 * Other Usage                                                             *
 * Alternatively, this file may be used in accordance with the terms and   *
 * conditions contained in a signed written agreement between you and      *
 * gempa GmbH.                                                             *
 ***************************************************************************/


#ifndef SEISCOMP_DATAMODEL_PARAMETERSET_H
#define SEISCOMP_DATAMODEL_PARAMETERSET_H


#include <string>
#include <seiscomp/core/datetime.h>
#include <vector>
#include <seiscomp/datamodel/comment.h>
#include <seiscomp/datamodel/notifier.h>
#include <seiscomp/datamodel/publicobject.h>
#include <seiscomp/core/exceptions.h>


namespace Seiscomp {
namespace DataModel {


DEFINE_SMARTPOINTER(ParameterSet);
DEFINE_SMARTPOINTER(Parameter);
DEFINE_SMARTPOINTER(Comment);

class Config;


class SC_SYSTEM_CORE_API ParameterSet : public PublicObject {
	DECLARE_SC_CLASS(ParameterSet)
	DECLARE_SERIALIZATION;
	DECLARE_METAOBJECT;

	// ------------------------------------------------------------------
	//  Xstruction
	// ------------------------------------------------------------------
	protected:
		//! Protected constructor
		ParameterSet();

	public:
		//! Copy constructor
		ParameterSet(const ParameterSet &other);

		//! Constructor with publicID
		ParameterSet(const std::string& publicID);

		//! Destructor
		~ParameterSet() override;


	// ------------------------------------------------------------------
	//  Creators
	// ------------------------------------------------------------------
	public:
		static ParameterSet *Create();
		static ParameterSet *Create(const std::string& publicID);


	// ------------------------------------------------------------------
	//  Lookup
	// ------------------------------------------------------------------
	public:
		static ParameterSet *Find(const std::string& publicID);


	// ------------------------------------------------------------------
	//  Operators
	// ------------------------------------------------------------------
	public:
		//! Copies the metadata of other to this
		//! No changes regarding child objects are made
		ParameterSet &operator=(const ParameterSet &other);
		//! Checks for equality of two objects. Child objects
		//! are not part of the check.
		bool operator==(const ParameterSet &other) const;
		bool operator!=(const ParameterSet &other) const;

		//! Wrapper that calls operator==
		bool equal(const ParameterSet &other) const;


	// ------------------------------------------------------------------
	//  Setters/Getters
	// ------------------------------------------------------------------
	public:
		void setBaseID(const std::string& baseID);
		const std::string& baseID() const;

		void setModuleID(const std::string& moduleID);
		const std::string& moduleID() const;

		void setCreated(const OPT(Seiscomp::Core::Time)& created);
		Seiscomp::Core::Time created() const;


	// ------------------------------------------------------------------
	//  Public interface
	// ------------------------------------------------------------------
	public:
		/**
		 * Add an object.
		 * @param obj The object pointer
		 * @return true The object has been added
		 * @return false The object has not been added
		 *               because it already exists in the list
		 *               or it already has another parent
		 */
		bool add(Parameter *obj);
		bool add(Comment *obj);

		/**
		 * Removes an object.
		 * @param obj The object pointer
		 * @return true The object has been removed
		 * @return false The object has not been removed
		 *               because it does not exist in the list
		 */
		bool remove(Parameter *obj);
		bool remove(Comment *obj);

		/**
		 * Removes an object of a particular class.
		 * @param i The object index
		 * @return true The object has been removed
		 * @return false The index is out of bounds
		 */
		bool removeParameter(size_t i);
		bool removeComment(size_t i);
		bool removeComment(const CommentIndex &i);

		//! Retrieve the number of objects of a particular class
		size_t parameterCount() const;
		size_t commentCount() const;

		//! Index access
		//! @return The object at index i
		Parameter *parameter(size_t i) const;

		Comment *comment(size_t i) const;
		Comment *comment(const CommentIndex &i) const;

		//! Find an object by its unique attribute(s)
		Parameter *findParameter(const std::string& publicID) const;

		Config *config() const;

		//! Implement Object interface
		bool assign(Object *other) override;
		bool attachTo(PublicObject *parent) override;
		bool detachFrom(PublicObject *parent) override;
		bool detach() override;

		//! Creates a clone
		Object *clone() const override;

		//! Implement PublicObject interface
		bool updateChild(Object *child) override;

		void accept(Visitor *visitor) override;


	// ------------------------------------------------------------------
	//  Implementation
	// ------------------------------------------------------------------
	private:
		// Attributes
		std::string _baseID;
		std::string _moduleID;
		OPT(Seiscomp::Core::Time) _created;

		// Aggregations
		std::vector<ParameterPtr> _parameters;
		std::vector<CommentPtr> _comments;

	DECLARE_SC_CLASSFACTORY_FRIEND(ParameterSet);
};


}
}


#endif
