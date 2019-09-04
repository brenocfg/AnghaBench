#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* qboolean ;
struct TYPE_9__ {scalar_t__ realTime; } ;
struct TYPE_14__ {size_t myTeamCount; scalar_t__* teamClientNums; scalar_t__ playerNumber; scalar_t__ newHighScoreTime; scalar_t__ newBestTime; int /*<<< orphan*/  demoAvailable; TYPE_2__ uiDC; void* soundHighScore; int /*<<< orphan*/  newHighScoreSound; TYPE_1__* gameTypes; scalar_t__ teamLeader; } ;
struct TYPE_13__ {size_t integer; } ;
struct TYPE_12__ {size_t integer; } ;
struct TYPE_11__ {scalar_t__ integer; } ;
struct TYPE_10__ {size_t integer; } ;
struct TYPE_8__ {scalar_t__ gtEnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_ANNOUNCER ; 
 scalar_t__ GT_FFA ; 
 scalar_t__ GT_TEAM ; 
 scalar_t__ UIAS_FAVORITES ; 
 int UI_SHOW_ANYNONTEAMGAME ; 
 int UI_SHOW_ANYTEAMGAME ; 
 int UI_SHOW_DEMOAVAILABLE ; 
 int UI_SHOW_FAVORITESERVERS ; 
 int UI_SHOW_FFA ; 
 int UI_SHOW_LEADER ; 
 int UI_SHOW_NETANYNONTEAMGAME ; 
 int UI_SHOW_NETANYTEAMGAME ; 
 int UI_SHOW_NEWBESTTIME ; 
 int UI_SHOW_NEWHIGHSCORE ; 
 int UI_SHOW_NOTFAVORITESERVERS ; 
 int UI_SHOW_NOTFFA ; 
 int UI_SHOW_NOTLEADER ; 
 void* qfalse ; 
 void* qtrue ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ uiInfo ; 
 TYPE_6__ ui_gameType ; 
 TYPE_5__ ui_netGameType ; 
 TYPE_4__ ui_netSource ; 
 TYPE_3__ ui_selectedPlayer ; 

__attribute__((used)) static qboolean UI_OwnerDrawVisible(int flags) {
	qboolean vis = qtrue;

	while (flags) {

		if (flags & UI_SHOW_FFA) {
			if (trap_Cvar_VariableValue("g_gametype") != GT_FFA) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_FFA;
		}

		if (flags & UI_SHOW_NOTFFA) {
			if (trap_Cvar_VariableValue("g_gametype") == GT_FFA) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NOTFFA;
		}

		if (flags & UI_SHOW_LEADER) {
			// these need to show when this client can give orders to a player or a group
			if (!uiInfo.teamLeader) {
				vis = qfalse;
			} else {
				// if showing yourself
				if (ui_selectedPlayer.integer < uiInfo.myTeamCount && uiInfo.teamClientNums[ui_selectedPlayer.integer] == uiInfo.playerNumber) { 
					vis = qfalse;
				}
			}
			flags &= ~UI_SHOW_LEADER;
		} 
		if (flags & UI_SHOW_NOTLEADER) {
			// these need to show when this client is assigning their own status or they are NOT the leader
			if (uiInfo.teamLeader) {
				// if not showing yourself
				if (!(ui_selectedPlayer.integer < uiInfo.myTeamCount && uiInfo.teamClientNums[ui_selectedPlayer.integer] == uiInfo.playerNumber)) { 
					vis = qfalse;
				}
				// these need to show when this client can give orders to a player or a group
			}
			flags &= ~UI_SHOW_NOTLEADER;
		} 
		if (flags & UI_SHOW_FAVORITESERVERS) {
			// this assumes you only put this type of display flag on something showing in the proper context
			if (ui_netSource.integer != UIAS_FAVORITES) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_FAVORITESERVERS;
		} 
		if (flags & UI_SHOW_NOTFAVORITESERVERS) {
			// this assumes you only put this type of display flag on something showing in the proper context
			if (ui_netSource.integer == UIAS_FAVORITES) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NOTFAVORITESERVERS;
		} 
		if (flags & UI_SHOW_ANYTEAMGAME) {
			if (uiInfo.gameTypes[ui_gameType.integer].gtEnum <= GT_TEAM ) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_ANYTEAMGAME;
		} 
		if (flags & UI_SHOW_ANYNONTEAMGAME) {
			if (uiInfo.gameTypes[ui_gameType.integer].gtEnum > GT_TEAM ) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_ANYNONTEAMGAME;
		} 
		if (flags & UI_SHOW_NETANYTEAMGAME) {
			if (uiInfo.gameTypes[ui_netGameType.integer].gtEnum <= GT_TEAM ) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NETANYTEAMGAME;
		} 
		if (flags & UI_SHOW_NETANYNONTEAMGAME) {
			if (uiInfo.gameTypes[ui_netGameType.integer].gtEnum > GT_TEAM ) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NETANYNONTEAMGAME;
		} 
		if (flags & UI_SHOW_NEWHIGHSCORE) {
			if (uiInfo.newHighScoreTime < uiInfo.uiDC.realTime) {
				vis = qfalse;
			} else {
				if (uiInfo.soundHighScore) {
					if (trap_Cvar_VariableValue("sv_killserver") == 0) {
						// wait on server to go down before playing sound
						trap_S_StartLocalSound(uiInfo.newHighScoreSound, CHAN_ANNOUNCER);
						uiInfo.soundHighScore = qfalse;
					}
				}
			}
			flags &= ~UI_SHOW_NEWHIGHSCORE;
		} 
		if (flags & UI_SHOW_NEWBESTTIME) {
			if (uiInfo.newBestTime < uiInfo.uiDC.realTime) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_NEWBESTTIME;
		} 
		if (flags & UI_SHOW_DEMOAVAILABLE) {
			if (!uiInfo.demoAvailable) {
				vis = qfalse;
			}
			flags &= ~UI_SHOW_DEMOAVAILABLE;
		} else {
			flags = 0;
		}
	}
  return vis;
}