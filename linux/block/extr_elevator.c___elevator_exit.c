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
struct request_queue {int dummy; } ;
struct elevator_queue {int /*<<< orphan*/  kobj; int /*<<< orphan*/  sysfs_lock; TYPE_2__* type; } ;
struct TYPE_3__ {scalar_t__ exit_sched; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_exit_sched (struct request_queue*,struct elevator_queue*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void __elevator_exit(struct request_queue *q, struct elevator_queue *e)
{
	mutex_lock(&e->sysfs_lock);
	if (e->type->ops.exit_sched)
		blk_mq_exit_sched(q, e);
	mutex_unlock(&e->sysfs_lock);

	kobject_put(&e->kobj);
}