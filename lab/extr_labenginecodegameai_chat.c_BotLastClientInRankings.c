#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* persistant; } ;
typedef  TYPE_1__ playerState_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int maxclients; } ;

/* Variables and functions */
 scalar_t__ BotAI_GetClientState (int,TYPE_1__*) ; 
 scalar_t__ CS_PLAYERS ; 
 int /*<<< orphan*/  EasyClientName (int,char*,int) ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 size_t PERS_SCORE ; 
 scalar_t__ TEAM_SPECTATOR ; 
 scalar_t__ atoi (char*) ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

char *BotLastClientInRankings(void) {
	int i, worstscore, bestclient;
	char buf[MAX_INFO_STRING];
	static char name[32];
	playerState_t ps;

	worstscore = 999999;
	bestclient = 0;
	for (i = 0; i < level.maxclients; i++) {
		trap_GetConfigstring(CS_PLAYERS+i, buf, sizeof(buf));
		//if no config string or no name
		if (!strlen(buf) || !strlen(Info_ValueForKey(buf, "n"))) continue;
		//skip spectators
		if (atoi(Info_ValueForKey(buf, "t")) == TEAM_SPECTATOR) continue;
		//
		if (BotAI_GetClientState(i, &ps) && ps.persistant[PERS_SCORE] < worstscore) {
			worstscore = ps.persistant[PERS_SCORE];
			bestclient = i;
		}
	}
	EasyClientName(bestclient, name, 32);
	return name;
}