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
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 int /*<<< orphan*/  Q_CleanStr (char*) ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

int ClientFromName(char *name) {
	int i;
	char buf[MAX_INFO_STRING];

	for (i = 0; i < level.maxclients; i++) {
		trap_GetConfigstring(CS_PLAYERS+i, buf, sizeof(buf));
		Q_CleanStr( buf );
		if (!Q_stricmp(Info_ValueForKey(buf, "n"), name)) return i;
	}
	return -1;
}