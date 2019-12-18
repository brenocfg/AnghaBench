#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_10__ {scalar_t__ lastchat_time; scalar_t__ ltgtype; double thinktime; scalar_t__ lastkilledplayer; scalar_t__ client; int /*<<< orphan*/  chatto; int /*<<< orphan*/  character; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_12__ {int /*<<< orphan*/  integer; } ;
struct TYPE_11__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BotIsObserver (TYPE_1__*) ; 
 int /*<<< orphan*/  BotMapTitle () ; 
 int BotNumActivePlayers () ; 
 int /*<<< orphan*/  BotRandomOpponentName (TYPE_1__*) ; 
 int /*<<< orphan*/  BotRandomWeaponName () ; 
 int /*<<< orphan*/  BotValidChatPosition (TYPE_1__*) ; 
 scalar_t__ BotVisibleEnemies (TYPE_1__*) ; 
 int /*<<< orphan*/  CHARACTERISTIC_CHAT_MISC ; 
 int /*<<< orphan*/  CHARACTERISTIC_CHAT_RANDOM ; 
 int /*<<< orphan*/  CHAT_ALL ; 
 int /*<<< orphan*/  EasyClientName (scalar_t__,char*,int) ; 
 scalar_t__ FloatTime () ; 
 scalar_t__ GT_TOURNAMENT ; 
 scalar_t__ LTG_RUSHBASE ; 
 scalar_t__ LTG_TEAMACCOMPANY ; 
 scalar_t__ LTG_TEAMHELP ; 
 scalar_t__ TIME_BETWEENCHATTING ; 
 scalar_t__ TeamPlayIsOn () ; 
 TYPE_3__ bot_fastchat ; 
 TYPE_2__ bot_nochat ; 
 scalar_t__ gametype ; 
 int qfalse ; 
 int qtrue ; 
 double random () ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 double trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_EA_Command (scalar_t__,char*) ; 

int BotChat_Random(bot_state_t *bs) {
	float rnd;
	char name[32];

	if (bot_nochat.integer) return qfalse;
	if (BotIsObserver(bs)) return qfalse;
	if (bs->lastchat_time > FloatTime() - TIME_BETWEENCHATTING) return qfalse;
	// don't chat in tournament mode
	if (gametype == GT_TOURNAMENT) return qfalse;
	//don't chat when doing something important :)
	if (bs->ltgtype == LTG_TEAMHELP ||
		bs->ltgtype == LTG_TEAMACCOMPANY ||
		bs->ltgtype == LTG_RUSHBASE) return qfalse;
	//
	rnd = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_RANDOM, 0, 1);
	if (random() > bs->thinktime * 0.1) return qfalse;
	if (!bot_fastchat.integer) {
		if (random() > rnd) return qfalse;
		if (random() > 0.25) return qfalse;
	}
	if (BotNumActivePlayers() <= 1) return qfalse;
	//
	if (!BotValidChatPosition(bs)) return qfalse;
	//
	if (BotVisibleEnemies(bs)) return qfalse;
	//
	if (bs->lastkilledplayer == bs->client) {
		strcpy(name, BotRandomOpponentName(bs));
	}
	else {
		EasyClientName(bs->lastkilledplayer, name, sizeof(name));
	}
	if (TeamPlayIsOn()) {
#ifdef MISSIONPACK
		trap_EA_Command(bs->client, "vtaunt");
#endif
		return qfalse;			// don't wait
	}
	//
	if (random() < trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_MISC, 0, 1)) {
		BotAI_BotInitialChat(bs, "random_misc",
					BotRandomOpponentName(bs),	// 0
					name,						// 1
					"[invalid var]",			// 2
					"[invalid var]",			// 3
					BotMapTitle(),				// 4
					BotRandomWeaponName(),		// 5
					NULL);
	}
	else {
		BotAI_BotInitialChat(bs, "random_insult",
					BotRandomOpponentName(bs),	// 0
					name,						// 1
					"[invalid var]",			// 2
					"[invalid var]",			// 3
					BotMapTitle(),				// 4
					BotRandomWeaponName(),		// 5
					NULL);
	}
	bs->lastchat_time = FloatTime();
	bs->chatto = CHAT_ALL;
	return qtrue;
}