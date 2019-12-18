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
struct request_queue {TYPE_1__* mq_ops; struct blk_mq_hw_ctx** queue_hw_ctx; int /*<<< orphan*/  queue_flags; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  poll_success; int /*<<< orphan*/  poll_invoked; int /*<<< orphan*/  poll_considered; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_5__ {long state; scalar_t__ plug; } ;
struct TYPE_4__ {int (* poll ) (struct blk_mq_hw_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_POLL ; 
 long TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (long) ; 
 int /*<<< orphan*/  blk_flush_plug_list (scalar_t__,int) ; 
 scalar_t__ blk_mq_poll_hybrid (struct request_queue*,struct blk_mq_hw_ctx*,int /*<<< orphan*/ ) ; 
 size_t blk_qc_t_to_queue_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_qc_t_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  need_resched () ; 
 scalar_t__ signal_pending_state (long,TYPE_2__*) ; 
 int stub1 (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int blk_poll(struct request_queue *q, blk_qc_t cookie, bool spin)
{
	struct blk_mq_hw_ctx *hctx;
	long state;

	if (!blk_qc_t_valid(cookie) ||
	    !test_bit(QUEUE_FLAG_POLL, &q->queue_flags))
		return 0;

	if (current->plug)
		blk_flush_plug_list(current->plug, false);

	hctx = q->queue_hw_ctx[blk_qc_t_to_queue_num(cookie)];

	/*
	 * If we sleep, have the caller restart the poll loop to reset
	 * the state. Like for the other success return cases, the
	 * caller is responsible for checking if the IO completed. If
	 * the IO isn't complete, we'll get called again and will go
	 * straight to the busy poll loop.
	 */
	if (blk_mq_poll_hybrid(q, hctx, cookie))
		return 1;

	hctx->poll_considered++;

	state = current->state;
	do {
		int ret;

		hctx->poll_invoked++;

		ret = q->mq_ops->poll(hctx);
		if (ret > 0) {
			hctx->poll_success++;
			__set_current_state(TASK_RUNNING);
			return ret;
		}

		if (signal_pending_state(state, current))
			__set_current_state(TASK_RUNNING);

		if (current->state == TASK_RUNNING)
			return 1;
		if (ret < 0 || !spin)
			break;
		cpu_relax();
	} while (!need_resched());

	__set_current_state(TASK_RUNNING);
	return 0;
}