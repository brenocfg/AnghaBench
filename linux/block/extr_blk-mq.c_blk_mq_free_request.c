#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  backing_dev_info; struct elevator_queue* elevator; } ;
struct TYPE_8__ {TYPE_3__* icq; } ;
struct request {int rq_flags; int /*<<< orphan*/  ref; int /*<<< orphan*/  state; TYPE_4__ elv; struct blk_mq_hw_ctx* mq_hctx; struct blk_mq_ctx* mq_ctx; struct request_queue* q; } ;
struct elevator_queue {TYPE_2__* type; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  nr_active; } ;
struct blk_mq_ctx {int /*<<< orphan*/ * rq_completed; } ;
struct TYPE_7__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* finish_request ) (struct request*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MQ_RQ_IDLE ; 
 int RQF_ELVPRIV ; 
 int RQF_MQ_INFLIGHT ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_mq_free_request (struct request*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  laptop_io_completion (int /*<<< orphan*/ ) ; 
 scalar_t__ laptop_mode ; 
 int /*<<< orphan*/  put_io_context (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 size_t rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  rq_qos_done (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request*) ; 
 scalar_t__ unlikely (int) ; 

void blk_mq_free_request(struct request *rq)
{
	struct request_queue *q = rq->q;
	struct elevator_queue *e = q->elevator;
	struct blk_mq_ctx *ctx = rq->mq_ctx;
	struct blk_mq_hw_ctx *hctx = rq->mq_hctx;

	if (rq->rq_flags & RQF_ELVPRIV) {
		if (e && e->type->ops.finish_request)
			e->type->ops.finish_request(rq);
		if (rq->elv.icq) {
			put_io_context(rq->elv.icq->ioc);
			rq->elv.icq = NULL;
		}
	}

	ctx->rq_completed[rq_is_sync(rq)]++;
	if (rq->rq_flags & RQF_MQ_INFLIGHT)
		atomic_dec(&hctx->nr_active);

	if (unlikely(laptop_mode && !blk_rq_is_passthrough(rq)))
		laptop_io_completion(q->backing_dev_info);

	rq_qos_done(q, rq);

	WRITE_ONCE(rq->state, MQ_RQ_IDLE);
	if (refcount_dec_and_test(&rq->ref))
		__blk_mq_free_request(rq);
}