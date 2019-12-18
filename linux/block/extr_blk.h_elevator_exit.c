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
struct elevator_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __elevator_exit (struct request_queue*,struct elevator_queue*) ; 
 int /*<<< orphan*/  blk_mq_sched_free_requests (struct request_queue*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void elevator_exit(struct request_queue *q,
		struct elevator_queue *e)
{
	lockdep_assert_held(&q->sysfs_lock);

	blk_mq_sched_free_requests(q);
	__elevator_exit(q, e);
}