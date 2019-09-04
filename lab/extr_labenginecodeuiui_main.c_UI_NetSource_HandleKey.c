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
typedef  int /*<<< orphan*/  masterstr ;
typedef  int /*<<< orphan*/  cvarname ;
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,scalar_t__) ; 
 scalar_t__ UIAS_GLOBAL0 ; 
 scalar_t__ UIAS_GLOBAL1 ; 
 scalar_t__ UIAS_GLOBAL5 ; 
 int /*<<< orphan*/  UI_BuildServerDisplayList (int /*<<< orphan*/ ) ; 
 int UI_SelectForKey (int) ; 
 int /*<<< orphan*/  UI_StartServerRefresh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ numNetSources ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,scalar_t__) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 TYPE_1__ ui_netSource ; 

__attribute__((used)) static qboolean UI_NetSource_HandleKey(int flags, float *special, int key) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		ui_netSource.integer += select;

		if(ui_netSource.integer >= UIAS_GLOBAL1 && ui_netSource.integer <= UIAS_GLOBAL5)
		{
			char masterstr[2], cvarname[sizeof("sv_master1")];
		
			while(ui_netSource.integer >= UIAS_GLOBAL1 && ui_netSource.integer <= UIAS_GLOBAL5)
			{
				Com_sprintf(cvarname, sizeof(cvarname), "sv_master%d", ui_netSource.integer - UIAS_GLOBAL0);
				trap_Cvar_VariableStringBuffer(cvarname, masterstr, sizeof(masterstr));
				if(*masterstr)
					break;

				ui_netSource.integer += select;
			}
		}

		if (ui_netSource.integer >= numNetSources) {
			ui_netSource.integer = 0;
		} else if (ui_netSource.integer < 0) {
			ui_netSource.integer = numNetSources - 1;
		}

		UI_BuildServerDisplayList(qtrue);
		UI_StartServerRefresh(qtrue, qfalse);
		trap_Cvar_SetValue( "ui_netSource", ui_netSource.integer);
		return qtrue;
	}
	return qfalse;
}