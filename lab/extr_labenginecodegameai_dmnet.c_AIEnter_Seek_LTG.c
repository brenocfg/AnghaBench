#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ainode; int /*<<< orphan*/  gs; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_7__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_2__ bot_goal_t ;

/* Variables and functions */
 int /*<<< orphan*/  AINode_Seek_LTG ; 
 int /*<<< orphan*/  BotRecordNodeSwitch (TYPE_1__*,char*,char*,char*) ; 
 scalar_t__ trap_BotGetTopGoal (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  trap_BotGoalName (int /*<<< orphan*/ ,char*,int) ; 

void AIEnter_Seek_LTG(bot_state_t *bs, char *s) {
	bot_goal_t goal;
	char buf[144];

	if (trap_BotGetTopGoal(bs->gs, &goal)) {
		trap_BotGoalName(goal.number, buf, 144);
		BotRecordNodeSwitch(bs, "seek LTG", buf, s);
	}
	else {
		BotRecordNodeSwitch(bs, "seek LTG", "no goal", s);
	}
	bs->ainode = AINode_Seek_LTG;
}