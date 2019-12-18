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
struct request_queue {int /*<<< orphan*/  sysfs_lock; } ;
struct elevator_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (struct request_queue*) ; 
 int elevator_switch_mq (struct request_queue*,struct elevator_type*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elevator_switch(struct request_queue *q, struct elevator_type *new_e)
{
	int err;

	lockdep_assert_held(&q->sysfs_lock);

	blk_mq_freeze_queue(q);
	blk_mq_quiesce_queue(q);

	err = elevator_switch_mq(q, new_e);

	blk_mq_unquiesce_queue(q);
	blk_mq_unfreeze_queue(q);

	return err;
}