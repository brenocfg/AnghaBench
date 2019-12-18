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
struct request_queue {TYPE_1__* mq_ops; } ;
struct request {int dummy; } ;
typedef  unsigned int blk_mq_req_flags_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* initialize_rq_fn ) (struct request*) ;} ;

/* Variables and functions */
 unsigned int BLK_MQ_REQ_NOWAIT ; 
 unsigned int BLK_MQ_REQ_PREEMPT ; 
 int /*<<< orphan*/  IS_ERR (struct request*) ; 
 unsigned int REQ_NOWAIT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned int) ; 
 struct request* blk_mq_alloc_request (struct request_queue*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct request*) ; 

struct request *blk_get_request(struct request_queue *q, unsigned int op,
				blk_mq_req_flags_t flags)
{
	struct request *req;

	WARN_ON_ONCE(op & REQ_NOWAIT);
	WARN_ON_ONCE(flags & ~(BLK_MQ_REQ_NOWAIT | BLK_MQ_REQ_PREEMPT));

	req = blk_mq_alloc_request(q, op, flags);
	if (!IS_ERR(req) && q->mq_ops->initialize_rq_fn)
		q->mq_ops->initialize_rq_fn(req);

	return req;
}