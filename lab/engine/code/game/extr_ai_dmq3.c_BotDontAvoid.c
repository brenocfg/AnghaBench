#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  gs; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_2__ bot_goal_t ;

/* Variables and functions */
 int trap_BotGetLevelItemGoal (int,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  trap_BotRemoveFromAvoidGoals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotDontAvoid(bot_state_t *bs, char *itemname) {
	bot_goal_t goal;
	int num;

	num = trap_BotGetLevelItemGoal(-1, itemname, &goal);
	while(num >= 0) {
		trap_BotRemoveFromAvoidGoals(bs->gs, goal.number);
		num = trap_BotGetLevelItemGoal(num, itemname, &goal);
	}
}