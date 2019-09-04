#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  teammatename ;
typedef  int /*<<< orphan*/  netname ;
struct TYPE_10__ {int /*<<< orphan*/  client; int /*<<< orphan*/  cs; int /*<<< orphan*/  teamleader; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_11__ {int subtype; } ;
typedef  TYPE_2__ bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_AFFIRMATIVE ; 
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,int /*<<< orphan*/ *) ; 
 int BotGetTeamMateTaskPreference (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BotSetTeamMateTaskPreference (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  BotVoiceChatOnly (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAT_TELL ; 
 int ClientFromName (char*) ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  EasyClientName (int,char*,int) ; 
 int MAX_MESSAGE_SIZE ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  NETNAME ; 
 scalar_t__ Q_stricmp (char*,int /*<<< orphan*/ ) ; 
#define  ST_ATTACKER 130 
#define  ST_DEFENDER 129 
#define  ST_ROAMER 128 
 int TEAMTP_ATTACKER ; 
 int TEAMTP_DEFENDER ; 
 int /*<<< orphan*/  VOICECHAT_YES ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMatchVariable (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_EA_Action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotMatch_TaskPreference(bot_state_t *bs, bot_match_t *match) {
	char netname[MAX_NETNAME];
	char teammatename[MAX_MESSAGE_SIZE];
	int teammate, preference;

	ClientName(bs->client, netname, sizeof(netname));
	if (Q_stricmp(netname, bs->teamleader) != 0) return;

	trap_BotMatchVariable(match, NETNAME, teammatename, sizeof(teammatename));
	teammate = ClientFromName(teammatename);
	if (teammate < 0) return;

	preference = BotGetTeamMateTaskPreference(bs, teammate);
	switch(match->subtype)
	{
		case ST_DEFENDER:
		{
			preference &= ~TEAMTP_ATTACKER;
			preference |= TEAMTP_DEFENDER;
			break;
		}
		case ST_ATTACKER:
		{
			preference &= ~TEAMTP_DEFENDER;
			preference |= TEAMTP_ATTACKER;
			break;
		}
		case ST_ROAMER:
		{
			preference &= ~(TEAMTP_ATTACKER|TEAMTP_DEFENDER);
			break;
		}
	}
	BotSetTeamMateTaskPreference(bs, teammate, preference);
	//
	EasyClientName(teammate, teammatename, sizeof(teammatename));
	BotAI_BotInitialChat(bs, "keepinmind", teammatename, NULL);
	trap_BotEnterChat(bs->cs, teammate, CHAT_TELL);
	BotVoiceChatOnly(bs, teammate, VOICECHAT_YES);
	trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
}