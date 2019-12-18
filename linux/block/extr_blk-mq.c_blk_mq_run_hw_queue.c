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
struct blk_mq_hw_ctx {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_mq_delay_run_hw_queue (struct blk_mq_hw_ctx*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_mq_hctx_has_pending (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_queue_quiesced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hctx_lock (struct blk_mq_hw_ctx*,int*) ; 
 int /*<<< orphan*/  hctx_unlock (struct blk_mq_hw_ctx*,int) ; 

bool blk_mq_run_hw_queue(struct blk_mq_hw_ctx *hctx, bool async)
{
	int srcu_idx;
	bool need_run;

	/*
	 * When queue is quiesced, we may be switching io scheduler, or
	 * updating nr_hw_queues, or other things, and we can't run queue
	 * any more, even __blk_mq_hctx_has_pending() can't be called safely.
	 *
	 * And queue will be rerun in blk_mq_unquiesce_queue() if it is
	 * quiesced.
	 */
	hctx_lock(hctx, &srcu_idx);
	need_run = !blk_queue_quiesced(hctx->queue) &&
		blk_mq_hctx_has_pending(hctx);
	hctx_unlock(hctx, srcu_idx);

	if (need_run) {
		__blk_mq_delay_run_hw_queue(hctx, async, 0);
		return true;
	}

	return false;
}