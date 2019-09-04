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

void BotCheckItemPickup(bot_state_t *bs, int *oldinventory) {
#ifdef MISSIONPACK
	int offence, leader;

	if (gametype <= GT_TEAM)
		return;

	offence = -1;
	// go into offence if picked up the kamikaze or invulnerability
	if (!oldinventory[INVENTORY_KAMIKAZE] && bs->inventory[INVENTORY_KAMIKAZE] >= 1) {
		offence = qtrue;
	}
	if (!oldinventory[INVENTORY_INVULNERABILITY] && bs->inventory[INVENTORY_INVULNERABILITY] >= 1) {
		offence = qtrue;
	}
	// if not already wearing the kamikaze or invulnerability
	if (!bs->inventory[INVENTORY_KAMIKAZE] && !bs->inventory[INVENTORY_INVULNERABILITY]) {
		if (!oldinventory[INVENTORY_SCOUT] && bs->inventory[INVENTORY_SCOUT] >= 1) {
			offence = qtrue;
		}
		if (!oldinventory[INVENTORY_GUARD] && bs->inventory[INVENTORY_GUARD] >= 1) {
			offence = qtrue;
		}
		if (!oldinventory[INVENTORY_DOUBLER] && bs->inventory[INVENTORY_DOUBLER] >= 1) {
			offence = qfalse;
		}
		if (!oldinventory[INVENTORY_AMMOREGEN] && bs->inventory[INVENTORY_AMMOREGEN] >= 1) {
			offence = qfalse;
		}
	}

	if (offence >= 0) {
		leader = ClientFromName(bs->teamleader);
		if (offence) {
			if (!(bs->teamtaskpreference & TEAMTP_ATTACKER)) {
				// if we have a bot team leader
				if (BotTeamLeader(bs)) {
					// tell the leader we want to be on offence
					BotVoiceChat(bs, leader, VOICECHAT_WANTONOFFENSE);
					//BotAI_BotInitialChat(bs, "wantoffence", NULL);
					//trap_BotEnterChat(bs->cs, leader, CHAT_TELL);
				}
				else if (g_spSkill.integer <= 3) {
					if ( bs->ltgtype != LTG_GETFLAG &&
						 bs->ltgtype != LTG_ATTACKENEMYBASE &&
						 bs->ltgtype != LTG_HARVEST ) {
						//
						if ((gametype != GT_CTF || (bs->redflagstatus == 0 && bs->blueflagstatus == 0)) &&
							(gametype != GT_1FCTF || bs->neutralflagstatus == 0) ) {
							// tell the leader we want to be on offence
							BotVoiceChat(bs, leader, VOICECHAT_WANTONOFFENSE);
							//BotAI_BotInitialChat(bs, "wantoffence", NULL);
							//trap_BotEnterChat(bs->cs, leader, CHAT_TELL);
						}
					}
				}
				bs->teamtaskpreference |= TEAMTP_ATTACKER;
			}
			bs->teamtaskpreference &= ~TEAMTP_DEFENDER;
		}
		else {
			if (!(bs->teamtaskpreference & TEAMTP_DEFENDER)) {
				// if we have a bot team leader
				if (BotTeamLeader(bs)) {
					// tell the leader we want to be on defense
					BotVoiceChat(bs, -1, VOICECHAT_WANTONDEFENSE);
					//BotAI_BotInitialChat(bs, "wantdefence", NULL);
					//trap_BotEnterChat(bs->cs, leader, CHAT_TELL);
				}
				else if (g_spSkill.integer <= 3) {
					if ( bs->ltgtype != LTG_DEFENDKEYAREA ) {
						//
						if ((gametype != GT_CTF || (bs->redflagstatus == 0 && bs->blueflagstatus == 0)) &&
							(gametype != GT_1FCTF || bs->neutralflagstatus == 0) ) {
							// tell the leader we want to be on defense
							BotVoiceChat(bs, -1, VOICECHAT_WANTONDEFENSE);
							//BotAI_BotInitialChat(bs, "wantdefence", NULL);
							//trap_BotEnterChat(bs->cs, leader, CHAT_TELL);
						}
					}
				}
				bs->teamtaskpreference |= TEAMTP_DEFENDER;
			}
			bs->teamtaskpreference &= ~TEAMTP_ATTACKER;
		}
	}
#endif
}