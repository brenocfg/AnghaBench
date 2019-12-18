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
struct request {struct request_queue* q; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (struct request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct request*) ; 

__attribute__((used)) static void __blk_mq_complete_request_remote(void *data)
{
	struct request *rq = data;
	struct request_queue *q = rq->q;

	q->mq_ops->complete(rq);
}