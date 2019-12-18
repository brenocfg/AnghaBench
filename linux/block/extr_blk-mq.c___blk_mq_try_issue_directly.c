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
struct request_queue {scalar_t__ elevator; } ;
struct request {struct request_queue* q; } ;
struct blk_mq_hw_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  __blk_mq_issue_directly (struct blk_mq_hw_ctx*,struct request*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blk_mq_get_dispatch_budget (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_get_driver_tag (struct request*) ; 
 scalar_t__ blk_mq_hctx_stopped (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_put_dispatch_budget (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_request_bypass_insert (struct request*,int) ; 
 scalar_t__ blk_queue_quiesced (struct request_queue*) ; 

__attribute__((used)) static blk_status_t __blk_mq_try_issue_directly(struct blk_mq_hw_ctx *hctx,
						struct request *rq,
						blk_qc_t *cookie,
						bool bypass_insert, bool last)
{
	struct request_queue *q = rq->q;
	bool run_queue = true;

	/*
	 * RCU or SRCU read lock is needed before checking quiesced flag.
	 *
	 * When queue is stopped or quiesced, ignore 'bypass_insert' from
	 * blk_mq_request_issue_directly(), and return BLK_STS_OK to caller,
	 * and avoid driver to try to dispatch again.
	 */
	if (blk_mq_hctx_stopped(hctx) || blk_queue_quiesced(q)) {
		run_queue = false;
		bypass_insert = false;
		goto insert;
	}

	if (q->elevator && !bypass_insert)
		goto insert;

	if (!blk_mq_get_dispatch_budget(hctx))
		goto insert;

	if (!blk_mq_get_driver_tag(rq)) {
		blk_mq_put_dispatch_budget(hctx);
		goto insert;
	}

	return __blk_mq_issue_directly(hctx, rq, cookie, last);
insert:
	if (bypass_insert)
		return BLK_STS_RESOURCE;

	blk_mq_request_bypass_insert(rq, run_queue);
	return BLK_STS_OK;
}