#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  var ;
struct TYPE_5__ {char* cvarName; int cvarFlags; int /*<<< orphan*/  defaultString; int /*<<< orphan*/ * vmCvar; } ;
typedef  TYPE_1__ cvarTable_t ;
struct TYPE_7__ {int /*<<< orphan*/  modificationCount; } ;
struct TYPE_6__ {int /*<<< orphan*/  localServer; } ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_USERINFO ; 
 int /*<<< orphan*/  DEFAULT_MODEL ; 
 int /*<<< orphan*/  DEFAULT_TEAM_HEAD ; 
 int /*<<< orphan*/  DEFAULT_TEAM_MODEL ; 
 int MAX_TOKEN_CHARS ; 
 int /*<<< orphan*/  atoi (char*) ; 
 TYPE_4__ cg_forceModel ; 
 TYPE_3__ cgs ; 
 TYPE_1__* cvarTable ; 
 int cvarTableSize ; 
 int /*<<< orphan*/  forceModelModificationCount ; 
 int /*<<< orphan*/  trap_Cvar_Register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 

void CG_RegisterCvars( void ) {
	int			i;
	cvarTable_t	*cv;
	char		var[MAX_TOKEN_CHARS];

	for ( i = 0, cv = cvarTable ; i < cvarTableSize ; i++, cv++ ) {
		trap_Cvar_Register( cv->vmCvar, cv->cvarName,
			cv->defaultString, cv->cvarFlags );
	}

	// see if we are also running the server on this machine
	trap_Cvar_VariableStringBuffer( "sv_running", var, sizeof( var ) );
	cgs.localServer = atoi( var );

	forceModelModificationCount = cg_forceModel.modificationCount;

	trap_Cvar_Register(NULL, "model", DEFAULT_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
	trap_Cvar_Register(NULL, "headmodel", DEFAULT_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
	trap_Cvar_Register(NULL, "team_model", DEFAULT_TEAM_MODEL, CVAR_USERINFO | CVAR_ARCHIVE );
	trap_Cvar_Register(NULL, "team_headmodel", DEFAULT_TEAM_HEAD, CVAR_USERINFO | CVAR_ARCHIVE );
}