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
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {int teamCount; TYPE_1__* teamList; } ;
struct TYPE_3__ {int /*<<< orphan*/  teamName; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_Cvar_VariableString (char*) ; 
 int UI_SelectForKey (int) ; 
 int UI_TeamIndexFromName (int /*<<< orphan*/ ) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ uiInfo ; 

__attribute__((used)) static qboolean UI_TeamName_HandleKey(int flags, float *special, int key, qboolean blue) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		int i;

		i = UI_TeamIndexFromName(UI_Cvar_VariableString((blue) ? "ui_blueTeam" : "ui_redTeam"));
		i += select;

		if (i >= uiInfo.teamCount) {
			i = 0;
		} else if (i < 0) {
			i = uiInfo.teamCount - 1;
		}

		trap_Cvar_Set( (blue) ? "ui_blueTeam" : "ui_redTeam", uiInfo.teamList[i].teamName);
		return qtrue;
	}
	return qfalse;
}