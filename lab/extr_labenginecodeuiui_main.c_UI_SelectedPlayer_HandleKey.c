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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int myTeamCount; char** teamNames; int /*<<< orphan*/  teamLeader; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_BuildPlayerList () ; 
 int UI_SelectForKey (int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 
 int trap_Cvar_VariableValue (char*) ; 
 TYPE_1__ uiInfo ; 

__attribute__((used)) static qboolean UI_SelectedPlayer_HandleKey(int flags, float *special, int key) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		int selected;

		UI_BuildPlayerList();
		if (!uiInfo.teamLeader) {
			return qfalse;
		}
		selected = trap_Cvar_VariableValue("cg_selectedPlayer");

		selected += select;

		if (selected > uiInfo.myTeamCount) {
			selected = 0;
		} else if (selected < 0) {
			selected = uiInfo.myTeamCount;
		}

		if (selected == uiInfo.myTeamCount) {
			trap_Cvar_Set( "cg_selectedPlayerName", "Everyone");
		} else {
			trap_Cvar_Set( "cg_selectedPlayerName", uiInfo.teamNames[selected]);
		}
		trap_Cvar_SetValue( "cg_selectedPlayer", selected);
	}
	return qfalse;
}