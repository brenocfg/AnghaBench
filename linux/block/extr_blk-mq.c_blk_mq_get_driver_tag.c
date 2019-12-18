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
struct request {int tag; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  internal_tag; int /*<<< orphan*/  cmd_flags; TYPE_2__* mq_hctx; int /*<<< orphan*/  q; } ;
struct blk_mq_alloc_data {TYPE_2__* hctx; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_flags; int /*<<< orphan*/  q; } ;
struct TYPE_4__ {TYPE_1__* tags; int /*<<< orphan*/  nr_active; int /*<<< orphan*/  sched_tags; } ;
struct TYPE_3__ {struct request** rqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_REQ_NOWAIT ; 
 int /*<<< orphan*/  BLK_MQ_REQ_RESERVED ; 
 int /*<<< orphan*/  RQF_MQ_INFLIGHT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int blk_mq_get_tag (struct blk_mq_alloc_data*) ; 
 int blk_mq_tag_busy (TYPE_2__*) ; 
 scalar_t__ blk_mq_tag_is_reserved (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool blk_mq_get_driver_tag(struct request *rq)
{
	struct blk_mq_alloc_data data = {
		.q = rq->q,
		.hctx = rq->mq_hctx,
		.flags = BLK_MQ_REQ_NOWAIT,
		.cmd_flags = rq->cmd_flags,
	};
	bool shared;

	if (rq->tag != -1)
		goto done;

	if (blk_mq_tag_is_reserved(data.hctx->sched_tags, rq->internal_tag))
		data.flags |= BLK_MQ_REQ_RESERVED;

	shared = blk_mq_tag_busy(data.hctx);
	rq->tag = blk_mq_get_tag(&data);
	if (rq->tag >= 0) {
		if (shared) {
			rq->rq_flags |= RQF_MQ_INFLIGHT;
			atomic_inc(&data.hctx->nr_active);
		}
		data.hctx->tags->rqs[rq->tag] = rq;
	}

done:
	return rq->tag != -1;
}