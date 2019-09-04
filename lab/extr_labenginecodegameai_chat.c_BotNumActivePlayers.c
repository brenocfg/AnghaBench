#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int maxclients; } ;

/* Variables and functions */
 scalar_t__ CS_PLAYERS ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 scalar_t__ TEAM_SPECTATOR ; 
 scalar_t__ atoi (char*) ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

int BotNumActivePlayers(void) {
	int i, num;
	char buf[MAX_INFO_STRING];

	num = 0;
	for (i = 0; i < level.maxclients; i++) {
		trap_GetConfigstring(CS_PLAYERS+i, buf, sizeof(buf));
		//if no config string or no name
		if (!strlen(buf) || !strlen(Info_ValueForKey(buf, "n"))) continue;
		//skip spectators
		if (atoi(Info_ValueForKey(buf, "t")) == TEAM_SPECTATOR) continue;
		//
		num++;
	}
	return num;
}