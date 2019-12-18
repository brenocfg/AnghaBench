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
struct request {int /*<<< orphan*/  queuelist; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
struct ace_device {int /*<<< orphan*/  fsm_tasklet; int /*<<< orphan*/  lock; int /*<<< orphan*/  rq_list; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {struct ace_device* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t ace_queue_rq(struct blk_mq_hw_ctx *hctx,
				 const struct blk_mq_queue_data *bd)
{
	struct ace_device *ace = hctx->queue->queuedata;
	struct request *req = bd->rq;

	if (blk_rq_is_passthrough(req)) {
		blk_mq_start_request(req);
		return BLK_STS_IOERR;
	}

	spin_lock_irq(&ace->lock);
	list_add_tail(&req->queuelist, &ace->rq_list);
	spin_unlock_irq(&ace->lock);

	tasklet_schedule(&ace->fsm_tasklet);
	return BLK_STS_OK;
}