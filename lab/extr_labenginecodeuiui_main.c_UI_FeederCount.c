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
struct TYPE_7__ {scalar_t__ realTime; } ;
struct TYPE_6__ {int numLines; } ;
struct TYPE_5__ {int numDisplayServers; } ;
struct TYPE_8__ {int q3HeadCount; int movieCount; int numFoundPlayerServers; scalar_t__ playerRefresh; int playerCount; int myTeamCount; int modCount; int demoCount; TYPE_3__ uiDC; TYPE_2__ serverStatusInfo; TYPE_1__ serverStatus; } ;

/* Variables and functions */
 float FEEDER_ALLMAPS ; 
 float FEEDER_CINEMATICS ; 
 float FEEDER_DEMOS ; 
 float FEEDER_FINDPLAYER ; 
 float FEEDER_HEADS ; 
 float FEEDER_MAPS ; 
 float FEEDER_MODS ; 
 float FEEDER_PLAYER_LIST ; 
 float FEEDER_Q3HEADS ; 
 float FEEDER_SERVERS ; 
 float FEEDER_SERVERSTATUS ; 
 float FEEDER_TEAM_LIST ; 
 int /*<<< orphan*/  UI_BuildPlayerList () ; 
 int UI_HeadCountByTeam () ; 
 int UI_MapCountByGameType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_4__ uiInfo ; 

__attribute__((used)) static int UI_FeederCount(float feederID) {
	if (feederID == FEEDER_HEADS) {
		return UI_HeadCountByTeam();
	} else if (feederID == FEEDER_Q3HEADS) {
		return uiInfo.q3HeadCount;
	} else if (feederID == FEEDER_CINEMATICS) {
		return uiInfo.movieCount;
	} else if (feederID == FEEDER_MAPS || feederID == FEEDER_ALLMAPS) {
		return UI_MapCountByGameType(feederID == FEEDER_MAPS ? qtrue : qfalse);
	} else if (feederID == FEEDER_SERVERS) {
		return uiInfo.serverStatus.numDisplayServers;
	} else if (feederID == FEEDER_SERVERSTATUS) {
		return uiInfo.serverStatusInfo.numLines;
	} else if (feederID == FEEDER_FINDPLAYER) {
		return uiInfo.numFoundPlayerServers;
	} else if (feederID == FEEDER_PLAYER_LIST) {
		if (uiInfo.uiDC.realTime > uiInfo.playerRefresh) {
			uiInfo.playerRefresh = uiInfo.uiDC.realTime + 3000;
			UI_BuildPlayerList();
		}
		return uiInfo.playerCount;
	} else if (feederID == FEEDER_TEAM_LIST) {
		if (uiInfo.uiDC.realTime > uiInfo.playerRefresh) {
			uiInfo.playerRefresh = uiInfo.uiDC.realTime + 3000;
			UI_BuildPlayerList();
		}
		return uiInfo.myTeamCount;
	} else if (feederID == FEEDER_MODS) {
		return uiInfo.modCount;
	} else if (feederID == FEEDER_DEMOS) {
		return uiInfo.demoCount;
	}
	return 0;
}