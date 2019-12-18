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
typedef  int /*<<< orphan*/  bot_state_t ;

/* Variables and functions */
 scalar_t__ BotTeam (int /*<<< orphan*/ *) ; 
 int CONTEXT_CTFBLUETEAM ; 
 int CONTEXT_CTFREDTEAM ; 
 int CONTEXT_HARVESTERBLUETEAM ; 
 int CONTEXT_HARVESTERREDTEAM ; 
 int CONTEXT_NAMES ; 
 int CONTEXT_NEARBYITEM ; 
 int CONTEXT_NORMAL ; 
 int CONTEXT_OBELISKBLUETEAM ; 
 int CONTEXT_OBELISKREDTEAM ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_HARVESTER ; 
 scalar_t__ GT_OBELISK ; 
 scalar_t__ TEAM_RED ; 
 scalar_t__ gametype ; 

int BotSynonymContext(bot_state_t *bs) {
	int context;

	context = CONTEXT_NORMAL|CONTEXT_NEARBYITEM|CONTEXT_NAMES;
	//
	if (gametype == GT_CTF
#ifdef MISSIONPACK
		|| gametype == GT_1FCTF
#endif
		) {
		if (BotTeam(bs) == TEAM_RED) context |= CONTEXT_CTFREDTEAM;
		else context |= CONTEXT_CTFBLUETEAM;
	}
#ifdef MISSIONPACK
	else if (gametype == GT_OBELISK) {
		if (BotTeam(bs) == TEAM_RED) context |= CONTEXT_OBELISKREDTEAM;
		else context |= CONTEXT_OBELISKBLUETEAM;
	}
	else if (gametype == GT_HARVESTER) {
		if (BotTeam(bs) == TEAM_RED) context |= CONTEXT_HARVESTERREDTEAM;
		else context |= CONTEXT_HARVESTERBLUETEAM;
	}
#endif
	return context;
}