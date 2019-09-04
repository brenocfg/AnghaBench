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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int numGameTypes; TYPE_1__* gameTypes; } ;
struct TYPE_5__ {int integer; } ;
struct TYPE_4__ {int gtEnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDER_ALLMAPS ; 
 int /*<<< orphan*/  Menu_SetFeederSelection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_MapCountByGameType (int /*<<< orphan*/ ) ; 
 int UI_SelectForKey (int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 
 TYPE_3__ uiInfo ; 
 TYPE_2__ ui_netGameType ; 

__attribute__((used)) static qboolean UI_NetGameType_HandleKey(int flags, float *special, int key) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		ui_netGameType.integer += select;

		if (ui_netGameType.integer < 0) {
			ui_netGameType.integer = uiInfo.numGameTypes - 1;
		} else if (ui_netGameType.integer >= uiInfo.numGameTypes) {
			ui_netGameType.integer = 0;
		}

		trap_Cvar_SetValue( "ui_netGameType", ui_netGameType.integer);
		trap_Cvar_SetValue( "ui_actualnetGameType", uiInfo.gameTypes[ui_netGameType.integer].gtEnum);
		trap_Cvar_SetValue( "ui_currentNetMap", 0);
		UI_MapCountByGameType(qfalse);
		Menu_SetFeederSelection(NULL, FEEDER_ALLMAPS, 0, NULL);
		return qtrue;
	}
	return qfalse;
}