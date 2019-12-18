#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
struct TYPE_7__ {int /*<<< orphan*/  client; int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_AFFIRMATIVE ; 
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,int /*<<< orphan*/ *) ; 
 int BotGetTeamMateTaskPreference (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BotSetTeamMateTaskPreference (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  BotVoiceChatOnly (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAT_TELL ; 
 int /*<<< orphan*/  EasyClientName (int,char*,int) ; 
 int MAX_NETNAME ; 
 int TEAMTP_ATTACKER ; 
 int TEAMTP_DEFENDER ; 
 int /*<<< orphan*/  VOICECHAT_YES ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_EA_Action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotVoiceChat_WantOnDefense(bot_state_t *bs, int client, int mode) {
	char netname[MAX_NETNAME];
	int preference;

	preference = BotGetTeamMateTaskPreference(bs, client);
	preference &= ~TEAMTP_ATTACKER;
	preference |= TEAMTP_DEFENDER;
	BotSetTeamMateTaskPreference(bs, client, preference);
	//
	EasyClientName(client, netname, sizeof(netname));
	BotAI_BotInitialChat(bs, "keepinmind", netname, NULL);
	trap_BotEnterChat(bs->cs, client, CHAT_TELL);
	BotVoiceChatOnly(bs, client, VOICECHAT_YES);
	trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
}