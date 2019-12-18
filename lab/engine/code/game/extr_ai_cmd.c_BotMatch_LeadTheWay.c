#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  teammate ;
typedef  int /*<<< orphan*/  netname ;
struct TYPE_15__ {scalar_t__ entitynum; } ;
struct TYPE_14__ {int entitynum; int areanum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  origin; } ;
struct TYPE_16__ {int client; int lead_teammate; int leadmessage_time; scalar_t__ leadvisible_time; scalar_t__ lead_time; int /*<<< orphan*/  cs; TYPE_2__ teamgoal; TYPE_1__ lead_teamgoal; } ;
typedef  TYPE_3__ bot_state_t ;
struct TYPE_17__ {int subtype; } ;
typedef  TYPE_4__ bot_match_t ;
struct TYPE_18__ {int /*<<< orphan*/  origin; scalar_t__ valid; } ;
typedef  TYPE_5__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_3__*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotAddressedToBot (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_5__*) ; 
 int BotPointAreaNum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotSameTeam (TYPE_3__*,int) ; 
 int /*<<< orphan*/  CHAT_TEAM ; 
 int ClientFromName (char*) ; 
 int FindClientByName (char*) ; 
 int FloatTime () ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  NETNAME ; 
 int ST_SOMEONE ; 
 int /*<<< orphan*/  TEAMMATE ; 
 scalar_t__ TEAM_LEAD_TIME ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int,int,int) ; 
 int qfalse ; 
 int qtrue ; 
 int random () ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMatchVariable (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 

void BotMatch_LeadTheWay(bot_state_t *bs, bot_match_t *match) {
	aas_entityinfo_t entinfo;
	char netname[MAX_MESSAGE_SIZE], teammate[MAX_MESSAGE_SIZE];
	int client, areanum, other;

	if (!TeamPlayIsOn()) return;
	//if not addressed to this bot
	if (!BotAddressedToBot(bs, match)) return;
	//if someone asks for someone else
	if (match->subtype & ST_SOMEONE) {
		//get the team mate name
		trap_BotMatchVariable(match, TEAMMATE, teammate, sizeof(teammate));
		client = FindClientByName(teammate);
		//if this is the bot self
		if (client == bs->client) {
			other = qfalse;
		}
		else if (!BotSameTeam(bs, client)) {
			//FIXME: say "I don't help the enemy"
			return;
		}
		else {
			other = qtrue;
		}
	}
	else {
		//get the netname
		trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
		client = ClientFromName(netname);
		other = qfalse;
	}
	//if the bot doesn't know who to help (FindClientByName returned -1)
	if (client < 0) {
		BotAI_BotInitialChat(bs, "whois", netname, NULL);
		trap_BotEnterChat(bs->cs, bs->client, CHAT_TEAM);
		return;
	}
	//
	bs->lead_teamgoal.entitynum = -1;
	BotEntityInfo(client, &entinfo);
	//if info is valid (in PVS)
	if (entinfo.valid) {
		areanum = BotPointAreaNum(entinfo.origin);
		if (areanum) { // && trap_AAS_AreaReachability(areanum)) {
			bs->lead_teamgoal.entitynum = client;
			bs->lead_teamgoal.areanum = areanum;
			VectorCopy(entinfo.origin, bs->lead_teamgoal.origin);
			VectorSet(bs->lead_teamgoal.mins, -8, -8, -8);
			VectorSet(bs->lead_teamgoal.maxs, 8, 8, 8);
		}
	}

	if (bs->teamgoal.entitynum < 0) {
		if (other) BotAI_BotInitialChat(bs, "whereis", teammate, NULL);
		else BotAI_BotInitialChat(bs, "whereareyou", netname, NULL);
		trap_BotEnterChat(bs->cs, bs->client, CHAT_TEAM);
		return;
	}
	bs->lead_teammate = client;
	bs->lead_time = FloatTime() + TEAM_LEAD_TIME;
	bs->leadvisible_time = 0;
	bs->leadmessage_time = -(FloatTime() + 2 * random());
}