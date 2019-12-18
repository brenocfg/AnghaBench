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
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  ainode; int /*<<< orphan*/  ms; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AINode_Battle_Fight ; 
 int /*<<< orphan*/  BFL_FIGHTSUICIDAL ; 
 int /*<<< orphan*/  BotRecordNodeSwitch (TYPE_1__*,char*,char*,char*) ; 
 int /*<<< orphan*/  trap_BotResetLastAvoidReach (int /*<<< orphan*/ ) ; 

void AIEnter_Battle_SuicidalFight(bot_state_t *bs, char *s) {
	BotRecordNodeSwitch(bs, "battle fight", "", s);
	trap_BotResetLastAvoidReach(bs->ms);
	bs->ainode = AINode_Battle_Fight;
	bs->flags |= BFL_FIGHTSUICIDAL;
}