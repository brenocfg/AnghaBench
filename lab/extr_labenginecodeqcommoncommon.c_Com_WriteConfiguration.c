#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  integer; } ;
struct TYPE_3__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 char const* BASEGAME ; 
 int CVAR_ARCHIVE ; 
 int /*<<< orphan*/  Com_WriteCDKey (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Com_WriteConfigToFile (int /*<<< orphan*/ ) ; 
 char* Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  Q3CONFIG_CFG ; 
 scalar_t__ UI_usesUniqueCDKey () ; 
 int /*<<< orphan*/ * cl_cdkey ; 
 int /*<<< orphan*/  com_fullyInitialized ; 
 TYPE_2__* com_standalone ; 
 TYPE_1__* com_writeConfig ; 
 int cvar_modifiedFlags ; 

void Com_WriteConfiguration( void ) {
	// if we are quiting without fully initializing, make sure
	// we don't write out anything
	if ( !com_fullyInitialized ) {
		return;
	}

	if ( !(cvar_modifiedFlags & CVAR_ARCHIVE ) ) {
		return;
	}
	cvar_modifiedFlags &= ~CVAR_ARCHIVE;

	if ( !com_writeConfig->integer ) {
		return;
	}

	Com_WriteConfigToFile( Q3CONFIG_CFG );

	// not needed for dedicated or standalone
#if !defined(DEDICATED) && !defined(STANDALONE)
	if(!com_standalone->integer)
	{
		const char *gamedir;
		gamedir = Cvar_VariableString( "fs_game" );
		if (UI_usesUniqueCDKey() && gamedir[0] != 0) {
			Com_WriteCDKey( gamedir, &cl_cdkey[16] );
		} else {
			Com_WriteCDKey( BASEGAME, cl_cdkey );
		}
	}
#endif
}