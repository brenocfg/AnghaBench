#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  message ;
struct TYPE_4__ {int id; } ;
struct TYPE_5__ {int curvalue; TYPE_1__ generic; } ;
typedef  TYPE_2__ menulist_s ;
struct TYPE_6__ {int selectedBot; scalar_t__ gametype; int /*<<< orphan*/ * botNames; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 scalar_t__ GT_CTF ; 
 int ID_LIST_BOTS ; 
 int ID_LIST_CTF_ORDERS ; 
 int ID_LIST_TEAM_ORDERS ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_TeamOrdersMenu_SetList (int) ; 
 int /*<<< orphan*/ * ctfMessages ; 
 int /*<<< orphan*/ * teamMessages ; 
 TYPE_3__ teamOrdersMenuInfo ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

__attribute__((used)) static void UI_TeamOrdersMenu_ListEvent( void *ptr, int event ) {
	int		id;
	int		selection;
	char	message[256];

	if (event != QM_ACTIVATED)
		return;

	id = ((menulist_s *)ptr)->generic.id;
	selection = ((menulist_s *)ptr)->curvalue;

	if( id == ID_LIST_BOTS ) {
		teamOrdersMenuInfo.selectedBot = selection;
		if( teamOrdersMenuInfo.gametype == GT_CTF ) {
			UI_TeamOrdersMenu_SetList( ID_LIST_CTF_ORDERS );
		}
		else {
			UI_TeamOrdersMenu_SetList( ID_LIST_TEAM_ORDERS );
		}
		return;
	}

	if( id == ID_LIST_CTF_ORDERS ) {
		Com_sprintf( message, sizeof(message), ctfMessages[selection], teamOrdersMenuInfo.botNames[teamOrdersMenuInfo.selectedBot] );
	}
	else {
		Com_sprintf( message, sizeof(message), teamMessages[selection], teamOrdersMenuInfo.botNames[teamOrdersMenuInfo.selectedBot] );
	}

	trap_Cmd_ExecuteText( EXEC_APPEND, va( "say_team \"%s\"\n", message ) );
	UI_PopMenu();
}