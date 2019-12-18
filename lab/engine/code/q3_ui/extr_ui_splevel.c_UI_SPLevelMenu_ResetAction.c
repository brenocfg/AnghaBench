#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 scalar_t__ UI_GetSpecialArenaInfo (char*) ; 
 int /*<<< orphan*/  UI_NewGame () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_SPLevelMenu () ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 

__attribute__((used)) static void UI_SPLevelMenu_ResetAction( qboolean result ) {
	if( !result ) {
		return;
	}

	// clear game variables
	UI_NewGame();
	if ( UI_GetSpecialArenaInfo( "training" ) ) {
		trap_Cvar_SetValue( "ui_spSelection", -4 );
	} else {
		trap_Cvar_SetValue( "ui_spSelection", 0 );
	}

	// make the level select menu re-initialize
	UI_PopMenu();
	UI_SPLevelMenu();
}