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
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/ * end_io; struct gendisk* rq_disk; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  rq_end_io_fn ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  blk_mq_sched_insert_request (struct request*,int,int,int) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 int irqs_disabled () ; 

void blk_execute_rq_nowait(struct request_queue *q, struct gendisk *bd_disk,
			   struct request *rq, int at_head,
			   rq_end_io_fn *done)
{
	WARN_ON(irqs_disabled());
	WARN_ON(!blk_rq_is_passthrough(rq));

	rq->rq_disk = bd_disk;
	rq->end_io = done;

	/*
	 * don't check dying flag for MQ because the request won't
	 * be reused after dying flag is set
	 */
	blk_mq_sched_insert_request(rq, at_head, true, false);
}