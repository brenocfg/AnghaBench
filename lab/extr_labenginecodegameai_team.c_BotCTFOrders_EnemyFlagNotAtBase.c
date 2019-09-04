#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  teammates ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  carriername ;
struct TYPE_8__ {int flagcarrier; int client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  BotSayTeamOrder (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BotSayVoiceTeamOrder (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int BotSortTeamMatesByBaseTravelTime (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  BotSortTeamMatesByTaskPreference (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  ClientName (int,char*,int) ; 
 int MAX_CLIENTS ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  VOICECHAT_DEFEND ; 
 int /*<<< orphan*/  VOICECHAT_FOLLOWFLAGCARRIER ; 
 int /*<<< orphan*/  VOICECHAT_FOLLOWME ; 
 int /*<<< orphan*/  VOICECHAT_GETFLAG ; 

void BotCTFOrders_EnemyFlagNotAtBase(bot_state_t *bs) {
	int numteammates, defenders, attackers, i, other;
	int teammates[MAX_CLIENTS];
	char name[MAX_NETNAME], carriername[MAX_NETNAME];

	numteammates = BotSortTeamMatesByBaseTravelTime(bs, teammates, sizeof(teammates));
	BotSortTeamMatesByTaskPreference(bs, teammates, numteammates);
	//different orders based on the number of team mates
	switch(numteammates) {
		case 1: break;
		case 2:
		{
			//tell the one not carrying the flag to defend the base
			if (teammates[0] == bs->flagcarrier) other = teammates[1];
			else other = teammates[0];
			ClientName(other, name, sizeof(name));
			BotAI_BotInitialChat(bs, "cmd_defendbase", name, NULL);
			BotSayTeamOrder(bs, other);
			BotSayVoiceTeamOrder(bs, other, VOICECHAT_DEFEND);
			break;
		}
		case 3:
		{
			//tell the one closest to the base not carrying the flag to defend the base
			if (teammates[0] != bs->flagcarrier) other = teammates[0];
			else other = teammates[1];
			ClientName(other, name, sizeof(name));
			BotAI_BotInitialChat(bs, "cmd_defendbase", name, NULL);
			BotSayTeamOrder(bs, other);
			BotSayVoiceTeamOrder(bs, other, VOICECHAT_DEFEND);
			//tell the other also to defend the base
			if (teammates[2] != bs->flagcarrier) other = teammates[2];
			else other = teammates[1];
			ClientName(other, name, sizeof(name));
			BotAI_BotInitialChat(bs, "cmd_defendbase", name, NULL);
			BotSayTeamOrder(bs, other);
			BotSayVoiceTeamOrder(bs, other, VOICECHAT_DEFEND);
			break;
		}
		default:
		{
			//60% will defend the base
			defenders = (int) (float) numteammates * 0.6 + 0.5;
			if (defenders > 6) defenders = 6;
			//30% accompanies the flag carrier
			attackers = (int) (float) numteammates * 0.3 + 0.5;
			if (attackers > 3) attackers = 3;
			for (i = 0; i < defenders; i++) {
				//
				if (teammates[i] == bs->flagcarrier) {
					continue;
				}
				ClientName(teammates[i], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_defendbase", name, NULL);
				BotSayTeamOrder(bs, teammates[i]);
				BotSayVoiceTeamOrder(bs, teammates[i], VOICECHAT_DEFEND);
			}
			// if we have a flag carrier
			if ( bs->flagcarrier != -1 ) {
				ClientName(bs->flagcarrier, carriername, sizeof(carriername));
				for (i = 0; i < attackers; i++) {
					//
					if (teammates[numteammates - i - 1] == bs->flagcarrier) {
						continue;
					}
					//
					ClientName(teammates[numteammates - i - 1], name, sizeof(name));
					if (bs->flagcarrier == bs->client) {
						BotAI_BotInitialChat(bs, "cmd_accompanyme", name, NULL);
						BotSayVoiceTeamOrder(bs, teammates[numteammates - i - 1], VOICECHAT_FOLLOWME);
					}
					else {
						BotAI_BotInitialChat(bs, "cmd_accompany", name, carriername, NULL);
						BotSayVoiceTeamOrder(bs, teammates[numteammates - i - 1], VOICECHAT_FOLLOWFLAGCARRIER);
					}
					BotSayTeamOrder(bs, teammates[numteammates - i - 1]);
				}
			}
			else {
				for (i = 0; i < attackers; i++) {
					//
					if (teammates[numteammates - i - 1] == bs->flagcarrier) {
						continue;
					}
					//
					ClientName(teammates[numteammates - i - 1], name, sizeof(name));
					BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
					BotSayVoiceTeamOrder(bs, teammates[numteammates - i - 1], VOICECHAT_GETFLAG);
					BotSayTeamOrder(bs, teammates[numteammates - i - 1]);
				}
			}
			//
			break;
		}
	}
}