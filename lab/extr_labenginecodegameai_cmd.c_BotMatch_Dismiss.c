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
typedef  int /*<<< orphan*/  netname ;
struct TYPE_5__ {int decisionmaker; int /*<<< orphan*/  cs; scalar_t__ lastgoal_ltgtype; scalar_t__ lead_time; scalar_t__ ltgtype; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotAddressedToBot (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHAT_TELL ; 
 int ClientFromName (char*) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  NETNAME ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMatchVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

void BotMatch_Dismiss(bot_state_t *bs, bot_match_t *match) {
	char netname[MAX_MESSAGE_SIZE];
	int client;

	if (!TeamPlayIsOn()) return;
	//if not addressed to this bot
	if (!BotAddressedToBot(bs, match)) return;
	trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
	client = ClientFromName(netname);
	//
	bs->decisionmaker = client;
	//
	bs->ltgtype = 0;
	bs->lead_time = 0;
	bs->lastgoal_ltgtype = 0;
	//
	BotAI_BotInitialChat(bs, "dismissed", NULL);
	trap_BotEnterChat(bs->cs, client, CHAT_TELL);
}