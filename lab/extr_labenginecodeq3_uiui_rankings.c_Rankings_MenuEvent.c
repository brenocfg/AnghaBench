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
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  ID_CREATE 133 
#define  ID_LEAVE 132 
#define  ID_LOGIN 131 
#define  ID_LOGOUT 130 
#define  ID_SETUP 129 
#define  ID_SPECTATE 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_ForceMenuOff () ; 
 int /*<<< orphan*/  UI_LoginMenu () ; 
 int /*<<< orphan*/  UI_SetupMenu () ; 
 int /*<<< orphan*/  UI_SignupMenu () ; 
 int /*<<< orphan*/  trap_CL_UI_RankUserRequestLogout () ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void Rankings_MenuEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_LOGIN:
		UI_LoginMenu();
		break;

	case ID_LOGOUT:
		// server side masqueraded player logout first
		trap_CL_UI_RankUserRequestLogout();
		UI_ForceMenuOff();
		break;
		
	case ID_CREATE:
		UI_SignupMenu();
		break;

	case ID_SPECTATE:
		trap_Cmd_ExecuteText( EXEC_APPEND, "cmd rank_spectate\n" );
		UI_ForceMenuOff();
		break;

	case ID_SETUP:
		UI_SetupMenu();
		break;
		
	case ID_LEAVE:
		trap_Cmd_ExecuteText( EXEC_APPEND, "disconnect\n" );
		UI_ForceMenuOff();
		break;

	}
}