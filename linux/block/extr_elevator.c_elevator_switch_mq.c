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
struct request_queue {TYPE_1__* elevator; int /*<<< orphan*/  sysfs_lock; } ;
struct elevator_type {int /*<<< orphan*/  elevator_name; } ;
struct TYPE_2__ {scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_add_trace_msg (struct request_queue*,char*,...) ; 
 int blk_mq_init_sched (struct request_queue*,struct elevator_type*) ; 
 int /*<<< orphan*/  elevator_exit (struct request_queue*,TYPE_1__*) ; 
 int elv_register_queue (struct request_queue*,int) ; 
 int /*<<< orphan*/  elv_unregister_queue (struct request_queue*) ; 
 int /*<<< orphan*/  ioc_clear_queue (struct request_queue*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int elevator_switch_mq(struct request_queue *q,
			      struct elevator_type *new_e)
{
	int ret;

	lockdep_assert_held(&q->sysfs_lock);

	if (q->elevator) {
		if (q->elevator->registered)
			elv_unregister_queue(q);

		ioc_clear_queue(q);
		elevator_exit(q, q->elevator);
	}

	ret = blk_mq_init_sched(q, new_e);
	if (ret)
		goto out;

	if (new_e) {
		ret = elv_register_queue(q, true);
		if (ret) {
			elevator_exit(q, q->elevator);
			goto out;
		}
	}

	if (new_e)
		blk_add_trace_msg(q, "elv switch: %s", new_e->elevator_name);
	else
		blk_add_trace_msg(q, "elv switch: none");

out:
	return ret;
}