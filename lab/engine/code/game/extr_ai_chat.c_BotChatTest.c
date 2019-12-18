#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_8__ {size_t client; size_t lastkilledby; size_t lastkilledplayer; int /*<<< orphan*/  cs; int /*<<< orphan*/  botdeathtype; } ;
typedef  TYPE_2__ bot_state_t ;
struct TYPE_9__ {TYPE_1__* client; } ;
struct TYPE_7__ {int /*<<< orphan*/  lasthurt_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_2__*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  BotFirstClientInRankings () ; 
 int /*<<< orphan*/  BotLastClientInRankings () ; 
 int /*<<< orphan*/  BotMapTitle () ; 
 int /*<<< orphan*/  BotRandomOpponentName (TYPE_2__*) ; 
 int /*<<< orphan*/  BotRandomWeaponName () ; 
 char* BotWeaponNameForMeansOfDeath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAT_ALL ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  EasyClientName (size_t,char*,int) ; 
 TYPE_3__* g_entities ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trap_BotNumInitialChats (int /*<<< orphan*/ ,char*) ; 

void BotChatTest(bot_state_t *bs) {

	char name[32];
	char *weap;
	int num, i;

	num = trap_BotNumInitialChats(bs->cs, "game_enter");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "game_enter",
					EasyClientName(bs->client, name, 32),	// 0
					BotRandomOpponentName(bs),				// 1
					"[invalid var]",						// 2
					"[invalid var]",						// 3
					BotMapTitle(),							// 4
					NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "game_exit");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "game_exit",
					EasyClientName(bs->client, name, 32),	// 0
					BotRandomOpponentName(bs),				// 1
					"[invalid var]",						// 2
					"[invalid var]",						// 3
					BotMapTitle(),							// 4
					NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "level_start");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "level_start",
					EasyClientName(bs->client, name, 32),	// 0
					NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "level_end_victory");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "level_end_victory",
				EasyClientName(bs->client, name, 32),	// 0
				BotRandomOpponentName(bs),				// 1
				BotFirstClientInRankings(),				// 2
				BotLastClientInRankings(),				// 3
				BotMapTitle(),							// 4
				NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "level_end_lose");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "level_end_lose",
				EasyClientName(bs->client, name, 32),	// 0
				BotRandomOpponentName(bs),				// 1
				BotFirstClientInRankings(),				// 2
				BotLastClientInRankings(),				// 3
				BotMapTitle(),							// 4
				NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "level_end");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "level_end",
				EasyClientName(bs->client, name, 32),	// 0
				BotRandomOpponentName(bs),				// 1
				BotFirstClientInRankings(),				// 2
				BotLastClientInRankings(),				// 3
				BotMapTitle(),							// 4
				NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	EasyClientName(bs->lastkilledby, name, sizeof(name));
	num = trap_BotNumInitialChats(bs->cs, "death_drown");
	for (i = 0; i < num; i++)
	{
		//
		BotAI_BotInitialChat(bs, "death_drown", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_slime");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_slime", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_lava");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_lava", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_cratered");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_cratered", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_suicide");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_suicide", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_telefrag");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_telefrag", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_gauntlet");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_gauntlet",
				name,												// 0
				BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
				NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_rail");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_rail",
				name,												// 0
				BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
				NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_bfg");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_bfg",
				name,												// 0
				BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
				NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_insult");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_insult",
					name,												// 0
					BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
					NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "death_praise");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "death_praise",
					name,												// 0
					BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
					NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	//
	EasyClientName(bs->lastkilledplayer, name, 32);
	//
	num = trap_BotNumInitialChats(bs->cs, "kill_gauntlet");
	for (i = 0; i < num; i++)
	{
		//
		BotAI_BotInitialChat(bs, "kill_gauntlet", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "kill_rail");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "kill_rail", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "kill_telefrag");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "kill_telefrag", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "kill_insult");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "kill_insult", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "kill_praise");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "kill_praise", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "enemy_suicide");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "enemy_suicide", name, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	ClientName(g_entities[bs->client].client->lasthurt_client, name, sizeof(name));
	weap = BotWeaponNameForMeansOfDeath(g_entities[bs->client].client->lasthurt_client);
	num = trap_BotNumInitialChats(bs->cs, "hit_talking");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "hit_talking", name, weap, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "hit_nodeath");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "hit_nodeath", name, weap, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "hit_nokill");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "hit_nokill", name, weap, NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	//
	if (bs->lastkilledplayer == bs->client) {
		strcpy(name, BotRandomOpponentName(bs));
	}
	else {
		EasyClientName(bs->lastkilledplayer, name, sizeof(name));
	}
	//
	num = trap_BotNumInitialChats(bs->cs, "random_misc");
	for (i = 0; i < num; i++)
	{
		//
		BotAI_BotInitialChat(bs, "random_misc",
					BotRandomOpponentName(bs),	// 0
					name,						// 1
					"[invalid var]",			// 2
					"[invalid var]",			// 3
					BotMapTitle(),				// 4
					BotRandomWeaponName(),		// 5
					NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
	num = trap_BotNumInitialChats(bs->cs, "random_insult");
	for (i = 0; i < num; i++)
	{
		BotAI_BotInitialChat(bs, "random_insult",
					BotRandomOpponentName(bs),	// 0
					name,						// 1
					"[invalid var]",			// 2
					"[invalid var]",			// 3
					BotMapTitle(),				// 4
					BotRandomWeaponName(),		// 5
					NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_ALL);
	}
}