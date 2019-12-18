#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ainode; int /*<<< orphan*/  chatto; int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AINode_Intermission ; 
 scalar_t__ BotChat_EndLevel (TYPE_1__*) ; 
 int /*<<< orphan*/  BotRecordNodeSwitch (TYPE_1__*,char*,char*,char*) ; 
 int /*<<< orphan*/  BotResetState (TYPE_1__*) ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void AIEnter_Intermission(bot_state_t *bs, char *s) {
	BotRecordNodeSwitch(bs, "intermission", "", s);
	//reset the bot state
	BotResetState(bs);
	//check for end level chat
	if (BotChat_EndLevel(bs)) {
		trap_BotEnterChat(bs->cs, 0, bs->chatto);
	}
	bs->ainode = AINode_Intermission;
}