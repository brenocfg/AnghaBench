#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {struct elevator_queue* elevator; } ;
struct elevator_queue {TYPE_2__* type; } ;
struct blk_mq_hw_ctx {scalar_t__ dispatch_busy; int /*<<< orphan*/  lock; int /*<<< orphan*/  dispatch; int /*<<< orphan*/  run; struct request_queue* queue; } ;
struct TYPE_3__ {scalar_t__ dispatch_request; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_mq_dispatch_rq_list (struct request_queue*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blk_mq_do_dispatch_ctx (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_do_dispatch_sched (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_flush_busy_ctxs (struct blk_mq_hw_ctx*,int /*<<< orphan*/ *) ; 
 scalar_t__ blk_mq_hctx_stopped (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_sched_mark_restart_hctx (struct blk_mq_hw_ctx*) ; 
 scalar_t__ blk_queue_quiesced (struct request_queue*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_list ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void blk_mq_sched_dispatch_requests(struct blk_mq_hw_ctx *hctx)
{
	struct request_queue *q = hctx->queue;
	struct elevator_queue *e = q->elevator;
	const bool has_sched_dispatch = e && e->type->ops.dispatch_request;
	LIST_HEAD(rq_list);

	/* RCU or SRCU read lock is needed before checking quiesced flag */
	if (unlikely(blk_mq_hctx_stopped(hctx) || blk_queue_quiesced(q)))
		return;

	hctx->run++;

	/*
	 * If we have previous entries on our dispatch list, grab them first for
	 * more fair dispatch.
	 */
	if (!list_empty_careful(&hctx->dispatch)) {
		spin_lock(&hctx->lock);
		if (!list_empty(&hctx->dispatch))
			list_splice_init(&hctx->dispatch, &rq_list);
		spin_unlock(&hctx->lock);
	}

	/*
	 * Only ask the scheduler for requests, if we didn't have residual
	 * requests from the dispatch list. This is to avoid the case where
	 * we only ever dispatch a fraction of the requests available because
	 * of low device queue depth. Once we pull requests out of the IO
	 * scheduler, we can no longer merge or sort them. So it's best to
	 * leave them there for as long as we can. Mark the hw queue as
	 * needing a restart in that case.
	 *
	 * We want to dispatch from the scheduler if there was nothing
	 * on the dispatch list or we were able to dispatch from the
	 * dispatch list.
	 */
	if (!list_empty(&rq_list)) {
		blk_mq_sched_mark_restart_hctx(hctx);
		if (blk_mq_dispatch_rq_list(q, &rq_list, false)) {
			if (has_sched_dispatch)
				blk_mq_do_dispatch_sched(hctx);
			else
				blk_mq_do_dispatch_ctx(hctx);
		}
	} else if (has_sched_dispatch) {
		blk_mq_do_dispatch_sched(hctx);
	} else if (hctx->dispatch_busy) {
		/* dequeue request one by one from sw queue if queue is busy */
		blk_mq_do_dispatch_ctx(hctx);
	} else {
		blk_mq_flush_busy_ctxs(hctx, &rq_list);
		blk_mq_dispatch_rq_list(q, &rq_list, false);
	}
}