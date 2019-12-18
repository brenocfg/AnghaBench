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
#define  ID_ADDBOTS 135 
#define  ID_QUIT 134 
#define  ID_REMOVEBOTS 133 
#define  ID_RESTART 132 
#define  ID_RESUME 131 
#define  ID_SERVERINFO 130 
#define  ID_SETUP 129 
#define  ID_TEAM 128 
 int /*<<< orphan*/  InGame_QuitAction ; 
 int /*<<< orphan*/  InGame_RestartAction ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_AddBotsMenu () ; 
 int /*<<< orphan*/  UI_ConfirmMenu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_RemoveBotsMenu () ; 
 int /*<<< orphan*/  UI_ServerInfoMenu () ; 
 int /*<<< orphan*/  UI_SetupMenu () ; 
 int /*<<< orphan*/  UI_TeamMainMenu () ; 

void InGame_Event( void *ptr, int notification ) {
	if( notification != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_TEAM:
		UI_TeamMainMenu();
		break;

	case ID_SETUP:
		UI_SetupMenu();
		break;

	case ID_RESTART:
		UI_ConfirmMenu( "RESTART ARENA?", 0, InGame_RestartAction );
		break;

	case ID_QUIT:
		UI_ConfirmMenu( "EXIT GAME?",  0, InGame_QuitAction );
		break;

	case ID_SERVERINFO:
		UI_ServerInfoMenu();
		break;

	case ID_ADDBOTS:
		UI_AddBotsMenu();
		break;

	case ID_REMOVEBOTS:
		UI_RemoveBotsMenu();
		break;

	case ID_RESUME:
		UI_PopMenu();
		break;
	}
}