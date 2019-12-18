#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ active; int /*<<< orphan*/  q_depth; int /*<<< orphan*/  queue; int /*<<< orphan*/  cmd_timer; struct creg_cmd* active_cmd; } ;
struct rsxx_cardinfo {TYPE_1__ creg_ctrl; } ;
struct creg_cmd {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rsxx_eeh_save_issued_creg(struct rsxx_cardinfo *card)
{
	struct creg_cmd *cmd = NULL;

	cmd = card->creg_ctrl.active_cmd;
	card->creg_ctrl.active_cmd = NULL;

	if (cmd) {
		del_timer_sync(&card->creg_ctrl.cmd_timer);

		spin_lock_bh(&card->creg_ctrl.lock);
		list_add(&cmd->list, &card->creg_ctrl.queue);
		card->creg_ctrl.q_depth++;
		card->creg_ctrl.active = 0;
		spin_unlock_bh(&card->creg_ctrl.lock);
	}
}