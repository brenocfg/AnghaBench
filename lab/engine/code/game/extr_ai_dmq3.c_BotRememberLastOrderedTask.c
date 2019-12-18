#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  teammate; int /*<<< orphan*/  lastgoal_teammate; int /*<<< orphan*/  teamgoal; int /*<<< orphan*/  lastgoal_teamgoal; int /*<<< orphan*/  ltgtype; int /*<<< orphan*/  lastgoal_ltgtype; int /*<<< orphan*/  decisionmaker; int /*<<< orphan*/  lastgoal_decisionmaker; int /*<<< orphan*/  ordered; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_goal_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void BotRememberLastOrderedTask(bot_state_t *bs) {
	if (!bs->ordered) {
		return;
	}
	bs->lastgoal_decisionmaker = bs->decisionmaker;
	bs->lastgoal_ltgtype = bs->ltgtype;
	memcpy(&bs->lastgoal_teamgoal, &bs->teamgoal, sizeof(bot_goal_t));
	bs->lastgoal_teammate = bs->teammate;
}