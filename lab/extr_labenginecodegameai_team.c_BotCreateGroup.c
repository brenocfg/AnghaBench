#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  leadername ;
struct TYPE_5__ {int client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  BotSayTeamOrderAlways (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ClientName (int,char*,int) ; 
 int MAX_NETNAME ; 

void BotCreateGroup(bot_state_t *bs, int *teammates, int groupsize) {
	char name[MAX_NETNAME], leadername[MAX_NETNAME];
	int i;

	// the others in the group will follow the teammates[0]
	ClientName(teammates[0], leadername, sizeof(leadername));
	for (i = 1; i < groupsize; i++)
	{
		ClientName(teammates[i], name, sizeof(name));
		if (teammates[0] == bs->client) {
			BotAI_BotInitialChat(bs, "cmd_accompanyme", name, NULL);
		}
		else {
			BotAI_BotInitialChat(bs, "cmd_accompany", name, leadername, NULL);
		}
		BotSayTeamOrderAlways(bs, teammates[i]);
	}
}