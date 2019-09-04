#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;

/* Variables and functions */
 int /*<<< orphan*/  BASETA ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  ID_CINEMATICS 135 
#define  ID_DEMOS 134 
#define  ID_EXIT 133 
#define  ID_MODS 132 
#define  ID_MULTIPLAYER 131 
#define  ID_SETUP 130 
#define  ID_SINGLEPLAYER 129 
#define  ID_TEAMARENA 128 
 int /*<<< orphan*/  MainMenu_ExitAction ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_ArenaServersMenu () ; 
 int /*<<< orphan*/  UI_CinematicsMenu () ; 
 int /*<<< orphan*/  UI_ConfirmMenu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DemosMenu () ; 
 int /*<<< orphan*/  UI_ModsMenu () ; 
 int /*<<< orphan*/  UI_SPLevelMenu () ; 
 int /*<<< orphan*/  UI_SetupMenu () ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 

void Main_MenuEvent (void* ptr, int event) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_SINGLEPLAYER:
		UI_SPLevelMenu();
		break;

	case ID_MULTIPLAYER:
		UI_ArenaServersMenu();
		break;

	case ID_SETUP:
		UI_SetupMenu();
		break;

	case ID_DEMOS:
		UI_DemosMenu();
		break;

	case ID_CINEMATICS:
		UI_CinematicsMenu();
		break;

	case ID_MODS:
		UI_ModsMenu();
		break;

	case ID_TEAMARENA:
		trap_Cvar_Set( "fs_game", BASETA);
		trap_Cmd_ExecuteText( EXEC_APPEND, "vid_restart;" );
		break;

	case ID_EXIT:
		UI_ConfirmMenu( "EXIT GAME?", 0, MainMenu_ExitAction );
		break;
	}
}