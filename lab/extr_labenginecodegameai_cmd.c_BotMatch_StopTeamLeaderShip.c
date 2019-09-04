#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  teammate ;
typedef  int /*<<< orphan*/  netname ;
struct TYPE_6__ {char* teamleader; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_7__ {int subtype; } ;
typedef  TYPE_2__ bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClientName (int,char*,int) ; 
 int FindClientByName (char*) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  NETNAME ; 
 int /*<<< orphan*/  Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 int ST_I ; 
 int /*<<< orphan*/  TEAMMATE ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 int /*<<< orphan*/ * notleader ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_BotMatchVariable (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 

void BotMatch_StopTeamLeaderShip(bot_state_t *bs, bot_match_t *match) {
	int client;
	char teammate[MAX_MESSAGE_SIZE];
	char netname[MAX_MESSAGE_SIZE];

	if (!TeamPlayIsOn()) return;
	//get the team mate that stops being the team leader
	trap_BotMatchVariable(match, TEAMMATE, teammate, sizeof(teammate));
	//if chats for him or herself
	if (match->subtype & ST_I) {
		trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
		client = FindClientByName(netname);
	}
	//chats for someone else
	else {
		client = FindClientByName(teammate);
	} //end else
	if (client >= 0) {
		if (!Q_stricmp(bs->teamleader, ClientName(client, netname, sizeof(netname)))) {
			bs->teamleader[0] = '\0';
			notleader[client] = qtrue;
		}
	}
}