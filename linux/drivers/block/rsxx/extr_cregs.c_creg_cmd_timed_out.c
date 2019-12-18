#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  creg_timeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; scalar_t__ active; TYPE_1__ creg_stats; struct creg_cmd* active_cmd; } ;
struct rsxx_cardinfo {TYPE_2__ creg_ctrl; } ;
struct creg_cmd {int /*<<< orphan*/  (* cb ) (struct rsxx_cardinfo*,struct creg_cmd*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  cmd_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 struct rsxx_cardinfo* card ; 
 int /*<<< orphan*/  creg_cmd_pool ; 
 TYPE_3__ creg_ctrl ; 
 int /*<<< orphan*/  creg_kick_queue (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct rsxx_cardinfo* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct creg_cmd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rsxx_cardinfo*,struct creg_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void creg_cmd_timed_out(struct timer_list *t)
{
	struct rsxx_cardinfo *card = from_timer(card, t, creg_ctrl.cmd_timer);
	struct creg_cmd *cmd;

	spin_lock(&card->creg_ctrl.lock);
	cmd = card->creg_ctrl.active_cmd;
	card->creg_ctrl.active_cmd = NULL;
	spin_unlock(&card->creg_ctrl.lock);

	if (cmd == NULL) {
		card->creg_ctrl.creg_stats.creg_timeout++;
		dev_warn(CARD_TO_DEV(card),
			"No active command associated with timeout!\n");
		return;
	}

	if (cmd->cb)
		cmd->cb(card, cmd, -ETIMEDOUT);

	kmem_cache_free(creg_cmd_pool, cmd);


	spin_lock(&card->creg_ctrl.lock);
	card->creg_ctrl.active = 0;
	creg_kick_queue(card);
	spin_unlock(&card->creg_ctrl.lock);
}