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
typedef  int /*<<< orphan*/  netname ;
typedef  int /*<<< orphan*/  bot_state_t ;
typedef  int /*<<< orphan*/  bot_match_t ;

/* Variables and functions */
 int FindClientByName (char*) ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  NETNAME ; 
 int /*<<< orphan*/ * notleader ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  trap_BotMatchVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

void BotMatch_EnterGame(bot_state_t *bs, bot_match_t *match) {
	int client;
	char netname[MAX_NETNAME];

	trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
	client = FindClientByName(netname);
	if (client >= 0) {
		notleader[client] = qfalse;
	}
	//NOTE: eliza chats will catch this
	//Com_sprintf(buf, sizeof(buf), "heya %s", netname);
	//EA_Say(bs->client, buf);
}