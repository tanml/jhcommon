/*
 * Copyright (c) 2010, JetHead Development, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the JetHead Development nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "JHCOM.h"
#include "jh_list.h"
#include <string>

using namespace JHCOM;

class ComponentManager : public IComponentManager
{
public:
	ComponentManager();
	
	ErrorCode LoadLibrary( const char *name );	
	ErrorCode RemoveModule( const char *name );

	IModule *GetModule( const char *name );
	ErrorCode UnloadLibrary( CID cid );

	ErrorCode CreateInstance( CID cid, IID iid, void **object );	
	ErrorCode GetService( CID cid, IID iid, void **object );	

	ErrorCode AddService( CID cid, ISupports *service );	
	ErrorCode RemoveService( CID cid );

	JHCOM_DECL_ISUPPORTS1( IComponentManager )

protected:
	virtual ~ComponentManager();

private:
	struct ClassInfo
	{
		ClassInfo( const CID &cid, ISupports *object = NULL ) : mCid( cid ), mClass( object ) {}
		
		bool operator==( ClassInfo &other ) { return other.mCid == mCid; }
		
		CID	mCid;
		ISupports *mClass;
	};

	struct ModuleInfo
	{
		ModuleInfo( const std::string &name, IModule *object = NULL, void *handle = NULL ) : 
			mName( name ), mModule( object ), mHandle( handle ) {}
		
		bool operator==( ModuleInfo &other ) { return other.mName == mName; }
		
		bool operator==( CID &cid ) 
		{ 
			if ( mModule == NULL ) 
				return false;
			else
				return cid == mModule->getCID(); 
		}
		
		std::string	mName;
		IModule *mModule;
		void *mHandle;
	};

	ModuleInfo *getModInfo( const char *name );
		
	JetHead::list<ClassInfo*> mClasses;
	JetHead::list<ModuleInfo*> mModules;
};


#endif // COMPONENTMANAGER_H_
