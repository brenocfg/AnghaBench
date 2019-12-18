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
struct request {scalar_t__ state; scalar_t__ q; } ;
struct blk_mq_hw_ctx {scalar_t__ queue; } ;

/* Variables and functions */
 scalar_t__ MQ_RQ_IN_FLIGHT ; 

__attribute__((used)) static bool blk_mq_rq_inflight(struct blk_mq_hw_ctx *hctx, struct request *rq,
			       void *priv, bool reserved)
{
	/*
	 * If we find a request that is inflight and the queue matches,
	 * we know the queue is busy. Return false to stop the iteration.
	 */
	if (rq->state == MQ_RQ_IN_FLIGHT && rq->q == hctx->queue) {
		bool *busy = priv;

		*busy = true;
		return false;
	}

	return true;
}