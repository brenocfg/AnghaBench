#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t tm_mon; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; } ;
typedef  TYPE_3__ qtime_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {scalar_t__ realTime; } ;
struct TYPE_7__ {scalar_t__ refreshtime; scalar_t__ numPlayersOnServers; scalar_t__ numDisplayServers; scalar_t__ nextDisplayRefresh; int /*<<< orphan*/  refreshActive; } ;
struct TYPE_11__ {TYPE_2__ uiDC; TYPE_1__ serverStatus; } ;
struct TYPE_10__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_NOW ; 
 int /*<<< orphan*/ * MonthAbbrev ; 
 scalar_t__ UIAS_GLOBAL0 ; 
 scalar_t__ UIAS_GLOBAL5 ; 
 scalar_t__ UIAS_LOCAL ; 
 char* UI_Cvar_VariableString (char*) ; 
 int UI_SourceForLAN () ; 
 int /*<<< orphan*/  UI_UpdatePendingPings () ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 scalar_t__ trap_LAN_GetServerCount (int) ; 
 int /*<<< orphan*/  trap_LAN_MarkServerVisible (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_LAN_ResetPings (int) ; 
 int /*<<< orphan*/  trap_RealTime (TYPE_3__*) ; 
 TYPE_5__ uiInfo ; 
 TYPE_4__ ui_netSource ; 
 char* va (char*,scalar_t__,...) ; 

__attribute__((used)) static void UI_StartServerRefresh(qboolean full, qboolean force)
{
	char	*ptr;
	int		lanSource;
	qtime_t q;

	// This function is called with force=qfalse when server browser menu opens or net source changes.
	// Automatically update local and favorite servers.
	// Only auto update master server list if there is no server info cache.
	if ( !force && ( ui_netSource.integer >= UIAS_GLOBAL0 && ui_netSource.integer <= UIAS_GLOBAL5 ) ) {
		if ( trap_LAN_GetServerCount( UI_SourceForLAN() ) > 0 ) {
			return; // have cached list
		}
	}

	trap_RealTime(&q);
	trap_Cvar_Set( va("ui_lastServerRefresh_%i", ui_netSource.integer), va("%s-%i, %i at %i:%02i", MonthAbbrev[q.tm_mon],q.tm_mday, 1900+q.tm_year,q.tm_hour,q.tm_min));

	if (!full) {
		UI_UpdatePendingPings();
		return;
	}

	uiInfo.serverStatus.refreshActive = qtrue;
	uiInfo.serverStatus.nextDisplayRefresh = uiInfo.uiDC.realTime + 1000;
	// clear number of displayed servers
	uiInfo.serverStatus.numDisplayServers = 0;
	uiInfo.serverStatus.numPlayersOnServers = 0;

	lanSource = UI_SourceForLAN();
	// mark all servers as visible so we store ping updates for them
	trap_LAN_MarkServerVisible(lanSource, -1, qtrue);
	// reset all the pings
	trap_LAN_ResetPings(lanSource);
	//
	if( ui_netSource.integer == UIAS_LOCAL ) {
		trap_Cmd_ExecuteText( EXEC_NOW, "localservers\n" );
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 5000;
		return;
	}

	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 5000;
	if( ui_netSource.integer >= UIAS_GLOBAL0 && ui_netSource.integer <= UIAS_GLOBAL5 ) {

		ptr = UI_Cvar_VariableString("debug_protocol");
		if (strlen(ptr)) {
			trap_Cmd_ExecuteText( EXEC_NOW, va( "globalservers %d %s full empty\n", ui_netSource.integer - UIAS_GLOBAL0, ptr ) );
		}
		else {
			trap_Cmd_ExecuteText( EXEC_NOW, va( "globalservers %d %d full empty\n", ui_netSource.integer - UIAS_GLOBAL0, (int)trap_Cvar_VariableValue( "protocol" ) ) );
		}
	}
}