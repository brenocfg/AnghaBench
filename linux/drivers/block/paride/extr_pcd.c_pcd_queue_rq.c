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
struct pcd_unit {int /*<<< orphan*/  rq_list; } ;
struct blk_mq_queue_data {TYPE_2__* rq; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_5__ {int /*<<< orphan*/  queuelist; } ;
struct TYPE_4__ {struct pcd_unit* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  blk_mq_start_request (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcd_lock ; 
 int /*<<< orphan*/  pcd_request () ; 
 scalar_t__ rq_data_dir (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t pcd_queue_rq(struct blk_mq_hw_ctx *hctx,
				 const struct blk_mq_queue_data *bd)
{
	struct pcd_unit *cd = hctx->queue->queuedata;

	if (rq_data_dir(bd->rq) != READ) {
		blk_mq_start_request(bd->rq);
		return BLK_STS_IOERR;
	}

	spin_lock_irq(&pcd_lock);
	list_add_tail(&bd->rq->queuelist, &cd->rq_list);
	pcd_request();
	spin_unlock_irq(&pcd_lock);

	return BLK_STS_OK;
}