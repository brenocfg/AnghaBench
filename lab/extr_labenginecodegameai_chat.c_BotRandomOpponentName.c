#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int client; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_6__ {int maxclients; } ;

/* Variables and functions */
 scalar_t__ BotSameTeam (TYPE_1__*,int) ; 
 scalar_t__ CS_PLAYERS ; 
 int /*<<< orphan*/  EasyClientName (int,char*,int) ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_CLIENTS ; 
 int MAX_INFO_STRING ; 
 scalar_t__ TEAM_SPECTATOR ; 
 scalar_t__ atoi (char*) ; 
 TYPE_2__ level ; 
 int random () ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

char *BotRandomOpponentName(bot_state_t *bs) {
	int i, count;
	char buf[MAX_INFO_STRING];
	int opponents[MAX_CLIENTS], numopponents;
	static char name[32];

	numopponents = 0;
	opponents[0] = 0;
	for (i = 0; i < level.maxclients; i++) {
		if (i == bs->client) continue;
		//
		trap_GetConfigstring(CS_PLAYERS+i, buf, sizeof(buf));
		//if no config string or no name
		if (!strlen(buf) || !strlen(Info_ValueForKey(buf, "n"))) continue;
		//skip spectators
		if (atoi(Info_ValueForKey(buf, "t")) == TEAM_SPECTATOR) continue;
		//skip team mates
		if (BotSameTeam(bs, i)) continue;
		//
		opponents[numopponents] = i;
		numopponents++;
	}
	count = random() * numopponents;
	for (i = 0; i < numopponents; i++) {
		count--;
		if (count <= 0) {
			EasyClientName(opponents[i], name, sizeof(name));
			return name;
		}
	}
	EasyClientName(opponents[0], name, sizeof(name));
	return name;
}