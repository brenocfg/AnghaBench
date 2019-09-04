#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_9__ {char* subteam; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_10__ {int subtype; scalar_t__ type; char* string; } ;
typedef  TYPE_2__ bot_match_t ;
typedef  int /*<<< orphan*/  addressedto ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESSEE ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int ClientOnSameTeamFromName (TYPE_1__*,char*) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  MORE ; 
 scalar_t__ MSG_CHATTELL ; 
 scalar_t__ MSG_EVERYONE ; 
 scalar_t__ MSG_MULTIPLENAMES ; 
 int /*<<< orphan*/  MTCONTEXT_ADDRESSEE ; 
 int /*<<< orphan*/  MTCONTEXT_REPLYCHAT ; 
 int /*<<< orphan*/  NETNAME ; 
 int NumPlayersOnSameTeam (TYPE_1__*) ; 
 int ST_ADDRESSED ; 
 int /*<<< orphan*/  TEAMMATE ; 
 int qfalse ; 
 int qtrue ; 
 float random () ; 
 scalar_t__ stristr (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ trap_BotFindMatch (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMatchVariable (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 

int BotAddressedToBot(bot_state_t *bs, bot_match_t *match) {
	char addressedto[MAX_MESSAGE_SIZE];
	char netname[MAX_MESSAGE_SIZE];
	char name[MAX_MESSAGE_SIZE];
	char botname[128];
	int client;
	bot_match_t addresseematch;

	trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
	client = ClientOnSameTeamFromName(bs, netname);
	if (client < 0) return qfalse;
	//if the message is addressed to someone
	if (match->subtype & ST_ADDRESSED) {
		trap_BotMatchVariable(match, ADDRESSEE, addressedto, sizeof(addressedto));
		//the name of this bot
		ClientName(bs->client, botname, 128);
		//
		while(trap_BotFindMatch(addressedto, &addresseematch, MTCONTEXT_ADDRESSEE)) {
			if (addresseematch.type == MSG_EVERYONE) {
				return qtrue;
			}
			else if (addresseematch.type == MSG_MULTIPLENAMES) {
				trap_BotMatchVariable(&addresseematch, TEAMMATE, name, sizeof(name));
				if (strlen(name)) {
					if (stristr(botname, name)) return qtrue;
					if (stristr(bs->subteam, name)) return qtrue;
				}
				trap_BotMatchVariable(&addresseematch, MORE, addressedto, MAX_MESSAGE_SIZE);
			}
			else {
				trap_BotMatchVariable(&addresseematch, TEAMMATE, name, MAX_MESSAGE_SIZE);
				if (strlen(name)) {
					if (stristr(botname, name)) return qtrue;
					if (stristr(bs->subteam, name)) return qtrue;
				}
				break;
			}
		}
		//Com_sprintf(buf, sizeof(buf), "not addressed to me but %s", addressedto);
		//trap_EA_Say(bs->client, buf);
		return qfalse;
	}
	else {
		bot_match_t tellmatch;

		tellmatch.type = 0;
		//if this message wasn't directed solely to this bot
		if (!trap_BotFindMatch(match->string, &tellmatch, MTCONTEXT_REPLYCHAT) ||
				tellmatch.type != MSG_CHATTELL) {
			//make sure not everyone reacts to this message
			if (random() > (float ) 1.0 / (NumPlayersOnSameTeam(bs)-1)) return qfalse;
		}
	}
	return qtrue;
}