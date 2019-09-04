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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {scalar_t__ numJoinGameTypes; } ;
struct TYPE_3__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_BuildServerDisplayList (int /*<<< orphan*/ ) ; 
 int UI_SelectForKey (int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,scalar_t__) ; 
 TYPE_2__ uiInfo ; 
 TYPE_1__ ui_joinGameType ; 

__attribute__((used)) static qboolean UI_JoinGameType_HandleKey(int flags, float *special, int key) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		ui_joinGameType.integer += select;

		if (ui_joinGameType.integer < 0) {
			ui_joinGameType.integer = uiInfo.numJoinGameTypes - 1;
		} else if (ui_joinGameType.integer >= uiInfo.numJoinGameTypes) {
			ui_joinGameType.integer = 0;
		}

		trap_Cvar_SetValue( "ui_joinGameType", ui_joinGameType.integer);
		UI_BuildServerDisplayList(qtrue);
		return qtrue;
	}
	return qfalse;
}