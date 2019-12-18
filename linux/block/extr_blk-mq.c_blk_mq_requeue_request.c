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
struct request {int /*<<< orphan*/  queuelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __blk_mq_requeue_request (struct request*) ; 
 int /*<<< orphan*/  blk_mq_add_to_requeue_list (struct request*,int,int) ; 
 int /*<<< orphan*/  blk_mq_sched_requeue_request (struct request*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void blk_mq_requeue_request(struct request *rq, bool kick_requeue_list)
{
	__blk_mq_requeue_request(rq);

	/* this request will be re-inserted to io scheduler queue */
	blk_mq_sched_requeue_request(rq);

	BUG_ON(!list_empty(&rq->queuelist));
	blk_mq_add_to_requeue_list(rq, true, kick_requeue_list);
}