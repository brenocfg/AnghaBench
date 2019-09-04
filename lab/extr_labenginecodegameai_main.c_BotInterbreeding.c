#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  client; scalar_t__ inuse; } ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAIShutdownClient (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXEC_INSERT ; 
 int /*<<< orphan*/  ExitLevel () ; 
 scalar_t__ GT_TOURNAMENT ; 
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  bot_interbreed ; 
 TYPE_4__ bot_interbreedbots ; 
 TYPE_1__ bot_interbreedchar ; 
 TYPE_2__** botstates ; 
 scalar_t__ gametype ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotLibVarSet (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Update (TYPE_1__*) ; 
 int /*<<< orphan*/  trap_SendConsoleCommand (int /*<<< orphan*/ ,char*) ; 
 char* va (char*,scalar_t__,...) ; 

void BotInterbreeding(void) {
	int i;

	trap_Cvar_Update(&bot_interbreedchar);
	if (!strlen(bot_interbreedchar.string)) return;
	//make sure we are in tournament mode
	if (gametype != GT_TOURNAMENT) {
		trap_Cvar_Set("g_gametype", va("%d", GT_TOURNAMENT));
		ExitLevel();
		return;
	}
	//shutdown all the bots
	for (i = 0; i < MAX_CLIENTS; i++) {
		if (botstates[i] && botstates[i]->inuse) {
			BotAIShutdownClient(botstates[i]->client, qfalse);
		}
	}
	//make sure all item weight configs are reloaded and Not shared
	trap_BotLibVarSet("bot_reloadcharacters", "1");
	//add a number of bots using the desired bot character
	for (i = 0; i < bot_interbreedbots.integer; i++) {
		trap_SendConsoleCommand( EXEC_INSERT, va("addbot %s 4 free %i %s%d\n",
						bot_interbreedchar.string, i * 50, bot_interbreedchar.string, i) );
	}
	//
	trap_Cvar_Set("bot_interbreedchar", "");
	bot_interbreed = qtrue;
}