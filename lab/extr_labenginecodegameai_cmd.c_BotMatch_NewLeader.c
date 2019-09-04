#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
struct TYPE_4__ {int /*<<< orphan*/  teamleader; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotSameTeam (TYPE_1__*,int) ; 
 int FindClientByName (char*) ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  NETNAME ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_BotMatchVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

void BotMatch_NewLeader(bot_state_t *bs, bot_match_t *match) {
	int client;
	char netname[MAX_NETNAME];

	trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
	client = FindClientByName(netname);
	if (!BotSameTeam(bs, client))
		return;
	Q_strncpyz(bs->teamleader, netname, sizeof(bs->teamleader));
}