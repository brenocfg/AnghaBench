#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* persistant; } ;
typedef  TYPE_2__ playerState_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int* persistant; } ;
struct TYPE_9__ {TYPE_1__ cur_ps; } ;
typedef  TYPE_3__ bot_state_t ;
struct TYPE_10__ {int maxclients; } ;

/* Variables and functions */
 scalar_t__ BotAI_GetClientState (int,TYPE_2__*) ; 
 scalar_t__ CS_PLAYERS ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 size_t PERS_SCORE ; 
 scalar_t__ TEAM_SPECTATOR ; 
 scalar_t__ atoi (char*) ; 
 TYPE_4__ level ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

int BotIsFirstInRankings(bot_state_t *bs) {
	int i, score;
	char buf[MAX_INFO_STRING];
	playerState_t ps;

	score = bs->cur_ps.persistant[PERS_SCORE];
	for (i = 0; i < level.maxclients; i++) {
		trap_GetConfigstring(CS_PLAYERS+i, buf, sizeof(buf));
		//if no config string or no name
		if (!strlen(buf) || !strlen(Info_ValueForKey(buf, "n"))) continue;
		//skip spectators
		if (atoi(Info_ValueForKey(buf, "t")) == TEAM_SPECTATOR) continue;
		//
		if (BotAI_GetClientState(i, &ps) && score < ps.persistant[PERS_SCORE]) return qfalse;
	}
	return qtrue;
}