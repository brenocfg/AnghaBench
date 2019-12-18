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
struct request_queue {unsigned int nr_hw_queues; TYPE_1__** queue_hw_ctx; } ;
struct request {int dummy; } ;
struct blk_mq_alloc_data {int flags; unsigned int cmd_flags; int /*<<< orphan*/  ctx; TYPE_1__* hctx; } ;
typedef  int blk_mq_req_flags_t ;
struct TYPE_2__ {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int BLK_MQ_REQ_NOWAIT ; 
 int EINVAL ; 
 int EIO ; 
 struct request* ERR_PTR (int) ; 
 int EWOULDBLOCK ; 
 int EXDEV ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __blk_mq_get_ctx (struct request_queue*,unsigned int) ; 
 struct request* blk_mq_get_request (struct request_queue*,int /*<<< orphan*/ *,struct blk_mq_alloc_data*) ; 
 int /*<<< orphan*/  blk_mq_hw_queue_mapped (TYPE_1__*) ; 
 int blk_queue_enter (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_exit (struct request_queue*) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_first_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct request *blk_mq_alloc_request_hctx(struct request_queue *q,
	unsigned int op, blk_mq_req_flags_t flags, unsigned int hctx_idx)
{
	struct blk_mq_alloc_data alloc_data = { .flags = flags, .cmd_flags = op };
	struct request *rq;
	unsigned int cpu;
	int ret;

	/*
	 * If the tag allocator sleeps we could get an allocation for a
	 * different hardware context.  No need to complicate the low level
	 * allocator for this for the rare use case of a command tied to
	 * a specific queue.
	 */
	if (WARN_ON_ONCE(!(flags & BLK_MQ_REQ_NOWAIT)))
		return ERR_PTR(-EINVAL);

	if (hctx_idx >= q->nr_hw_queues)
		return ERR_PTR(-EIO);

	ret = blk_queue_enter(q, flags);
	if (ret)
		return ERR_PTR(ret);

	/*
	 * Check if the hardware context is actually mapped to anything.
	 * If not tell the caller that it should skip this queue.
	 */
	alloc_data.hctx = q->queue_hw_ctx[hctx_idx];
	if (!blk_mq_hw_queue_mapped(alloc_data.hctx)) {
		blk_queue_exit(q);
		return ERR_PTR(-EXDEV);
	}
	cpu = cpumask_first_and(alloc_data.hctx->cpumask, cpu_online_mask);
	alloc_data.ctx = __blk_mq_get_ctx(q, cpu);

	rq = blk_mq_get_request(q, NULL, &alloc_data);
	blk_queue_exit(q);

	if (!rq)
		return ERR_PTR(-EWOULDBLOCK);

	return rq;
}