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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int /*<<< orphan*/  inuse; } ;
struct TYPE_4__ {int maxclients; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotSetInfoConfigString (TYPE_2__*) ; 
 scalar_t__ CS_PLAYERS ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 TYPE_2__** botstates ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

void BotUpdateInfoConfigStrings(void) {
	int i;
	char buf[MAX_INFO_STRING];

	for (i = 0; i < level.maxclients; i++) {
		//
		if ( !botstates[i] || !botstates[i]->inuse )
			continue;
		//
		trap_GetConfigstring(CS_PLAYERS+i, buf, sizeof(buf));
		//if no config string or no name
		if (!strlen(buf) || !strlen(Info_ValueForKey(buf, "n")))
			continue;
		BotSetInfoConfigString(botstates[i]);
	}
}