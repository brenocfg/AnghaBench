#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ realTime; } ;
struct TYPE_13__ {scalar_t__ nextDisplayRefresh; int motdLen; int motdWidth; scalar_t__ refreshtime; scalar_t__ numPlayersOnServers; scalar_t__ numDisplayServers; int /*<<< orphan*/  motd; } ;
struct TYPE_20__ {TYPE_3__ uiDC; TYPE_2__ serverStatus; TYPE_1__* joinGameTypes; } ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {size_t integer; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {size_t integer; } ;
struct TYPE_12__ {int gtEnum; } ;
struct TYPE_11__ {int /*<<< orphan*/  basedir; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDER_SERVERS ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_STRING_CHARS ; 
 int /*<<< orphan*/  Menu_SetFeederSelection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UIAS_FAVORITES ; 
 scalar_t__ UIAS_LOCAL ; 
 int /*<<< orphan*/  UI_BinaryServerInsertion (int) ; 
 int /*<<< orphan*/  UI_RemoveServerFromDisplayList (int) ; 
 int UI_SourceForLAN () ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int qtrue ; 
 TYPE_10__* serverFilters ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,int /*<<< orphan*/ ,int) ; 
 int trap_LAN_GetServerCount (int) ; 
 int /*<<< orphan*/  trap_LAN_GetServerInfo (int,int,char*,int) ; 
 int trap_LAN_GetServerPing (int,int) ; 
 int /*<<< orphan*/  trap_LAN_MarkServerVisible (int,int,int) ; 
 int /*<<< orphan*/  trap_LAN_ServerIsVisible (int,int) ; 
 TYPE_9__ uiInfo ; 
 TYPE_8__ ui_browserShowEmpty ; 
 TYPE_7__ ui_browserShowFull ; 
 TYPE_6__ ui_joinGameType ; 
 TYPE_5__ ui_netSource ; 
 TYPE_4__ ui_serverFilterType ; 

__attribute__((used)) static void UI_BuildServerDisplayList(int force) {
	int i, count, clients, maxClients, ping, game, len, visible;
	char info[MAX_STRING_CHARS];
//	qboolean startRefresh = qtrue; TTimo: unused
	static int numinvisible;
	int	lanSource;

	if (!(force || uiInfo.uiDC.realTime > uiInfo.serverStatus.nextDisplayRefresh)) {
		return;
	}
	// if we shouldn't reset
	if ( force == 2 ) {
		force = 0;
	}

	// do motd updates here too
	trap_Cvar_VariableStringBuffer( "cl_motdString", uiInfo.serverStatus.motd, sizeof(uiInfo.serverStatus.motd) );
	len = strlen(uiInfo.serverStatus.motd);
	if (len == 0) {
		strcpy(uiInfo.serverStatus.motd, "Welcome to Team Arena!");
		len = strlen(uiInfo.serverStatus.motd);
	} 
	if (len != uiInfo.serverStatus.motdLen) {
		uiInfo.serverStatus.motdLen = len;
		uiInfo.serverStatus.motdWidth = -1;
	} 

	lanSource = UI_SourceForLAN();

	if (force) {
		numinvisible = 0;
		// clear number of displayed servers
		uiInfo.serverStatus.numDisplayServers = 0;
		uiInfo.serverStatus.numPlayersOnServers = 0;
		// set list box index to zero
		Menu_SetFeederSelection(NULL, FEEDER_SERVERS, 0, NULL);
		// mark all servers as visible so we store ping updates for them
		trap_LAN_MarkServerVisible(lanSource, -1, qtrue);
	}

	// get the server count (comes from the master)
	count = trap_LAN_GetServerCount(lanSource);
	if (count == -1 || (ui_netSource.integer == UIAS_LOCAL && count == 0) ) {
		// still waiting on a response from the master
		uiInfo.serverStatus.numDisplayServers = 0;
		uiInfo.serverStatus.numPlayersOnServers = 0;
		uiInfo.serverStatus.nextDisplayRefresh = uiInfo.uiDC.realTime + 500;
		return;
	}

	visible = qfalse;
	for (i = 0; i < count; i++) {
		// if we already got info for this server
		if (!trap_LAN_ServerIsVisible(lanSource, i)) {
			continue;
		}
		visible = qtrue;
		// get the ping for this server
		ping = trap_LAN_GetServerPing(lanSource, i);
		if (ping > 0 || ui_netSource.integer == UIAS_FAVORITES) {
			// Remove favorite servers so they do not appear multiple times
			// or appear when the cached server info was not filtered out
			// but the new server info is filtered out.
			if (ui_netSource.integer == UIAS_FAVORITES) {
				UI_RemoveServerFromDisplayList(i);
			}

			trap_LAN_GetServerInfo(lanSource, i, info, MAX_STRING_CHARS);

			clients = atoi(Info_ValueForKey(info, "clients"));

			if (ui_browserShowEmpty.integer == 0) {
				if (clients == 0) {
					if (ping > 0) {
						trap_LAN_MarkServerVisible(lanSource, i, qfalse);
					}
					continue;
				}
			}

			if (ui_browserShowFull.integer == 0) {
				maxClients = atoi(Info_ValueForKey(info, "sv_maxclients"));
				if (clients == maxClients) {
					if (ping > 0) {
						trap_LAN_MarkServerVisible(lanSource, i, qfalse);
					}
					continue;
				}
			}

			if (uiInfo.joinGameTypes[ui_joinGameType.integer].gtEnum != -1) {
				game = atoi(Info_ValueForKey(info, "gametype"));
				if (game != uiInfo.joinGameTypes[ui_joinGameType.integer].gtEnum) {
					if (ping > 0) {
						trap_LAN_MarkServerVisible(lanSource, i, qfalse);
					}
					continue;
				}
			}
				
			if (ui_serverFilterType.integer > 0) {
				if (Q_stricmp(Info_ValueForKey(info, "game"), serverFilters[ui_serverFilterType.integer].basedir) != 0) {
					if (ping > 0) {
						trap_LAN_MarkServerVisible(lanSource, i, qfalse);
					}
					continue;
				}
			}
			// insert the server into the list
			UI_BinaryServerInsertion(i);
			// done with this server
			if (ping > 0) {
				trap_LAN_MarkServerVisible(lanSource, i, qfalse);
				uiInfo.serverStatus.numPlayersOnServers += clients;
				numinvisible++;
			}
		}
	}

	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime;

	// if there were no servers visible for ping updates
	if (!visible) {
//		UI_StopServerRefresh();
//		uiInfo.serverStatus.nextDisplayRefresh = 0;
	}
}