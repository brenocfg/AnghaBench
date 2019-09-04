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
struct TYPE_8__ {int ctfstrategy; int numteammates; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotSayTeamOrder (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BotSayVoiceTeamOrder (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int BotSortTeamMatesByBaseTravelTime (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  BotSortTeamMatesByTaskPreference (TYPE_1__*,int*,int) ; 
 int CTFS_AGRESSIVE ; 
 int /*<<< orphan*/  ClientName (int,char*,int) ; 
 int MAX_CLIENTS ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  VOICECHAT_DEFEND ; 
 int /*<<< orphan*/  VOICECHAT_GETFLAG ; 

void BotCTFOrders_FlagNotAtBase(bot_state_t *bs) {
	int numteammates, defenders, attackers, i;
	int teammates[MAX_CLIENTS];
	char name[MAX_NETNAME];

	numteammates = BotSortTeamMatesByBaseTravelTime(bs, teammates, sizeof(teammates));
	BotSortTeamMatesByTaskPreference(bs, teammates, numteammates);
	//passive strategy
	if (!(bs->ctfstrategy & CTFS_AGRESSIVE)) {
		//different orders based on the number of team mates
		switch(bs->numteammates) {
			case 1: break;
			case 2:
			{
				// keep one near the base for when the flag is returned
				ClientName(teammates[0], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_defendbase", name, NULL);
				BotSayTeamOrder(bs, teammates[0]);
				BotSayVoiceTeamOrder(bs, teammates[0], VOICECHAT_DEFEND);
				//
				ClientName(teammates[1], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
				BotSayTeamOrder(bs, teammates[1]);
				BotSayVoiceTeamOrder(bs, teammates[1], VOICECHAT_GETFLAG);
				break;
			}
			case 3:
			{
				//keep one near the base for when the flag is returned
				ClientName(teammates[0], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_defendbase", name, NULL);
				BotSayTeamOrder(bs, teammates[0]);
				BotSayVoiceTeamOrder(bs, teammates[0], VOICECHAT_DEFEND);
				//the other two get the flag
				ClientName(teammates[1], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
				BotSayTeamOrder(bs, teammates[1]);
				BotSayVoiceTeamOrder(bs, teammates[1], VOICECHAT_GETFLAG);
				//
				ClientName(teammates[2], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
				BotSayTeamOrder(bs, teammates[2]);
				BotSayVoiceTeamOrder(bs, teammates[2], VOICECHAT_GETFLAG);
				break;
			}
			default:
			{
				//keep some people near the base for when the flag is returned
				defenders = (int) (float) numteammates * 0.3 + 0.5;
				if (defenders > 3) defenders = 3;
				attackers = (int) (float) numteammates * 0.6 + 0.5;
				if (attackers > 6) attackers = 6;
				for (i = 0; i < defenders; i++) {
					//
					ClientName(teammates[i], name, sizeof(name));
					BotAI_BotInitialChat(bs, "cmd_defendbase", name, NULL);
					BotSayTeamOrder(bs, teammates[i]);
					BotSayVoiceTeamOrder(bs, teammates[i], VOICECHAT_DEFEND);
				}
				for (i = 0; i < attackers; i++) {
					//
					ClientName(teammates[numteammates - i - 1], name, sizeof(name));
					BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
					BotSayTeamOrder(bs, teammates[numteammates - i - 1]);
					BotSayVoiceTeamOrder(bs, teammates[0], VOICECHAT_GETFLAG);
				}
				//
				break;
			}
		}
	}
	else {
		//different orders based on the number of team mates
		switch(bs->numteammates) {
			case 1: break;
			case 2:
			{
				//both will go for the enemy flag
				ClientName(teammates[0], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
				BotSayTeamOrder(bs, teammates[0]);
				BotSayVoiceTeamOrder(bs, teammates[0], VOICECHAT_GETFLAG);
				//
				ClientName(teammates[1], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
				BotSayTeamOrder(bs, teammates[1]);
				BotSayVoiceTeamOrder(bs, teammates[1], VOICECHAT_GETFLAG);
				break;
			}
			case 3:
			{
				//everyone go for the flag
				ClientName(teammates[0], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
				BotSayTeamOrder(bs, teammates[0]);
				BotSayVoiceTeamOrder(bs, teammates[0], VOICECHAT_GETFLAG);
				//
				ClientName(teammates[1], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
				BotSayTeamOrder(bs, teammates[1]);
				BotSayVoiceTeamOrder(bs, teammates[1], VOICECHAT_GETFLAG);
				//
				ClientName(teammates[2], name, sizeof(name));
				BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
				BotSayTeamOrder(bs, teammates[2]);
				BotSayVoiceTeamOrder(bs, teammates[2], VOICECHAT_GETFLAG);
				break;
			}
			default:
			{
				//keep some people near the base for when the flag is returned
				defenders = (int) (float) numteammates * 0.2 + 0.5;
				if (defenders > 2) defenders = 2;
				attackers = (int) (float) numteammates * 0.7 + 0.5;
				if (attackers > 7) attackers = 7;
				for (i = 0; i < defenders; i++) {
					//
					ClientName(teammates[i], name, sizeof(name));
					BotAI_BotInitialChat(bs, "cmd_defendbase", name, NULL);
					BotSayTeamOrder(bs, teammates[i]);
					BotSayVoiceTeamOrder(bs, teammates[i], VOICECHAT_DEFEND);
				}
				for (i = 0; i < attackers; i++) {
					//
					ClientName(teammates[numteammates - i - 1], name, sizeof(name));
					BotAI_BotInitialChat(bs, "cmd_getflag", name, NULL);
					BotSayTeamOrder(bs, teammates[numteammates - i - 1]);
					BotSayVoiceTeamOrder(bs, teammates[numteammates - i - 1], VOICECHAT_GETFLAG);
				}
				//
				break;
			}
		}
	}
}