#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct request {int /*<<< orphan*/  queuelist; struct blk_mq_hw_ctx* mq_hctx; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  lock; int /*<<< orphan*/  dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_run_hw_queue (struct blk_mq_hw_ctx*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void blk_mq_request_bypass_insert(struct request *rq, bool run_queue)
{
	struct blk_mq_hw_ctx *hctx = rq->mq_hctx;

	spin_lock(&hctx->lock);
	list_add_tail(&rq->queuelist, &hctx->dispatch);
	spin_unlock(&hctx->lock);

	if (run_queue)
		blk_mq_run_hw_queue(hctx, false);
}