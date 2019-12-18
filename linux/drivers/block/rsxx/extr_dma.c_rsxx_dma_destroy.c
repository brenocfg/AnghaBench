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
struct TYPE_6__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  buf; } ;
struct rsxx_dma_ctrl {TYPE_3__ cmd; TYPE_1__ status; int /*<<< orphan*/  trackers; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  activity_timer; int /*<<< orphan*/ * done_wq; int /*<<< orphan*/ * issue_wq; } ;
struct rsxx_cardinfo {int n_targets; TYPE_2__* dev; struct rsxx_dma_ctrl* ctrl; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_BUFFER_SIZE8 ; 
 int /*<<< orphan*/  COMPLETE_DMA ; 
 int /*<<< orphan*/  STATUS_BUFFER_SIZE8 ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_cleanup_dma_queue (struct rsxx_dma_ctrl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_dma_cancel (struct rsxx_dma_ctrl*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void rsxx_dma_destroy(struct rsxx_cardinfo *card)
{
	struct rsxx_dma_ctrl *ctrl;
	int i;

	for (i = 0; i < card->n_targets; i++) {
		ctrl = &card->ctrl[i];

		if (ctrl->issue_wq) {
			destroy_workqueue(ctrl->issue_wq);
			ctrl->issue_wq = NULL;
		}

		if (ctrl->done_wq) {
			destroy_workqueue(ctrl->done_wq);
			ctrl->done_wq = NULL;
		}

		if (timer_pending(&ctrl->activity_timer))
			del_timer_sync(&ctrl->activity_timer);

		/* Clean up the DMA queue */
		spin_lock_bh(&ctrl->queue_lock);
		rsxx_cleanup_dma_queue(ctrl, &ctrl->queue, COMPLETE_DMA);
		spin_unlock_bh(&ctrl->queue_lock);

		rsxx_dma_cancel(ctrl);

		vfree(ctrl->trackers);

		dma_free_coherent(&card->dev->dev, STATUS_BUFFER_SIZE8,
				  ctrl->status.buf, ctrl->status.dma_addr);
		dma_free_coherent(&card->dev->dev, COMMAND_BUFFER_SIZE8,
				  ctrl->cmd.buf, ctrl->cmd.dma_addr);
	}
}