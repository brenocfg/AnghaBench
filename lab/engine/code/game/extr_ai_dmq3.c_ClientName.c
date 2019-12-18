#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ CS_PLAYERS ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_CLIENTS ; 
 int MAX_INFO_STRING ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  Q_CleanStr (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

char *ClientName(int client, char *name, int size) {
	char buf[MAX_INFO_STRING];

	if (client < 0 || client >= MAX_CLIENTS) {
		BotAI_Print(PRT_ERROR, "ClientName: client out of range\n");
		return "[client out of range]";
	}
	trap_GetConfigstring(CS_PLAYERS+client, buf, sizeof(buf));
	strncpy(name, Info_ValueForKey(buf, "n"), size-1);
	name[size-1] = '\0';
	Q_CleanStr( name );
	return name;
}