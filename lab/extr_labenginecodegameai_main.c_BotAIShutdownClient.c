#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_7__ {int inuse; int /*<<< orphan*/  patrolpoints; int /*<<< orphan*/  checkpoints; int /*<<< orphan*/  character; int /*<<< orphan*/  ws; int /*<<< orphan*/  cs; int /*<<< orphan*/  gs; int /*<<< orphan*/  ms; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 scalar_t__ BotChat_ExitGame (TYPE_1__*) ; 
 int /*<<< orphan*/  BotClearActivateGoalStack (TYPE_1__*) ; 
 int /*<<< orphan*/  BotFreeWaypoints (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BotWriteSessionData (TYPE_1__*) ; 
 int /*<<< orphan*/  CHAT_ALL ; 
 TYPE_1__** botstates ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numbots ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotFreeCharacter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotFreeChatState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotFreeGoalState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotFreeMoveState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotFreeWeaponState (int /*<<< orphan*/ ) ; 

int BotAIShutdownClient(int client, qboolean restart) {
	bot_state_t *bs;

	bs = botstates[client];
	if (!bs || !bs->inuse) {
		//BotAI_Print(PRT_ERROR, "BotAIShutdownClient: client %d already shutdown\n", client);
		return qfalse;
	}

	if (restart) {
		BotWriteSessionData(bs);
	}

	if (BotChat_ExitGame(bs)) {
		trap_BotEnterChat(bs->cs, bs->client, CHAT_ALL);
	}

	trap_BotFreeMoveState(bs->ms);
	//free the goal state
	trap_BotFreeGoalState(bs->gs);
	//free the chat file
	trap_BotFreeChatState(bs->cs);
	//free the weapon weights
	trap_BotFreeWeaponState(bs->ws);
	//free the bot character
	trap_BotFreeCharacter(bs->character);
	//
	BotFreeWaypoints(bs->checkpoints);
	BotFreeWaypoints(bs->patrolpoints);
	//clear activate goal stack
	BotClearActivateGoalStack(bs);
	//clear the bot state
	memset(bs, 0, sizeof(bot_state_t));
	//set the inuse flag to qfalse
	bs->inuse = qfalse;
	//there's one bot less
	numbots--;
	//everything went ok
	return qtrue;
}