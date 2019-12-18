#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pd_unit {int /*<<< orphan*/  rq_list; } ;
struct blk_mq_queue_data {TYPE_2__* rq; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_5__ {int /*<<< orphan*/  queuelist; } ;
struct TYPE_4__ {struct pd_unit* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  blk_mq_start_request (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_lock ; 
 TYPE_2__* pd_req ; 
 int /*<<< orphan*/  run_fsm () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t pd_queue_rq(struct blk_mq_hw_ctx *hctx,
				const struct blk_mq_queue_data *bd)
{
	struct pd_unit *disk = hctx->queue->queuedata;

	spin_lock_irq(&pd_lock);
	if (!pd_req) {
		pd_req = bd->rq;
		blk_mq_start_request(pd_req);
	} else
		list_add_tail(&bd->rq->queuelist, &disk->rq_list);
	spin_unlock_irq(&pd_lock);

	run_fsm();
	return BLK_STS_OK;
}