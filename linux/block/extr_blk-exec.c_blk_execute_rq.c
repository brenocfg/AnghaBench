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
struct request {int /*<<< orphan*/ * end_io_data; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  blk_end_sync_rq ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (struct request_queue*,struct gendisk*,struct request*,int,int /*<<< orphan*/ ) ; 
 unsigned long sysctl_hung_task_timeout_secs ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_io_timeout (int /*<<< orphan*/ *,unsigned long) ; 

void blk_execute_rq(struct request_queue *q, struct gendisk *bd_disk,
		   struct request *rq, int at_head)
{
	DECLARE_COMPLETION_ONSTACK(wait);
	unsigned long hang_check;

	rq->end_io_data = &wait;
	blk_execute_rq_nowait(q, bd_disk, rq, at_head, blk_end_sync_rq);

	/* Prevent hang_check timer from firing at us during very long I/O */
	hang_check = sysctl_hung_task_timeout_secs;
	if (hang_check)
		while (!wait_for_completion_io_timeout(&wait, hang_check * (HZ/2)));
	else
		wait_for_completion_io(&wait);
}