#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_5__ {scalar_t__ realTime; } ;
struct TYPE_6__ {scalar_t__ refreshtime; int /*<<< orphan*/  refreshActive; } ;
struct TYPE_8__ {TYPE_1__ uiDC; TYPE_2__ serverStatus; } ;
struct TYPE_7__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_GLOBAL ; 
 int /*<<< orphan*/  AS_LOCAL ; 
 int /*<<< orphan*/  EXEC_NOW ; 
 scalar_t__ UIAS_FAVORITES ; 
 scalar_t__ UIAS_LOCAL ; 
 int /*<<< orphan*/  UI_BuildServerDisplayList (int) ; 
 int /*<<< orphan*/  UI_SourceForLAN () ; 
 int /*<<< orphan*/  UI_StopServerRefresh () ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ trap_LAN_GetServerCount (int /*<<< orphan*/ ) ; 
 scalar_t__ trap_LAN_UpdateVisiblePings (int /*<<< orphan*/ ) ; 
 TYPE_4__ uiInfo ; 
 TYPE_3__ ui_netSource ; 

__attribute__((used)) static void UI_DoServerRefresh( void )
{
	qboolean wait = qfalse;

	if (!uiInfo.serverStatus.refreshActive) {
		return;
	}
	if (ui_netSource.integer != UIAS_FAVORITES) {
		if (ui_netSource.integer == UIAS_LOCAL) {
			if (!trap_LAN_GetServerCount(AS_LOCAL)) {
				wait = qtrue;
			}
		} else {
			if (trap_LAN_GetServerCount(AS_GLOBAL) < 0) {
				wait = qtrue;
			}
		}
	}

	if (uiInfo.uiDC.realTime < uiInfo.serverStatus.refreshtime) {
		if (wait) {
			return;
		}
	}

	// if still trying to retrieve pings
	if (trap_LAN_UpdateVisiblePings(UI_SourceForLAN())) {
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 1000;
	} else if (!wait) {
		// get the last servers in the list
		UI_BuildServerDisplayList(2);
		// stop the refresh
		UI_StopServerRefresh();
	} else if ( ui_netSource.integer == UIAS_LOCAL ) {
		// no local servers found, check again
		trap_Cmd_ExecuteText( EXEC_NOW, "localservers\n" );
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 5000;
	}
	//
	UI_BuildServerDisplayList(qfalse);
}