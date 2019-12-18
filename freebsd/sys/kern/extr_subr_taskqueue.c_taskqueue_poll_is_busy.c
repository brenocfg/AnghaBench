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
struct taskqueue {int dummy; } ;
struct task {scalar_t__ ta_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 scalar_t__ task_is_running (struct taskqueue*,struct task*) ; 

int
taskqueue_poll_is_busy(struct taskqueue *queue, struct task *task)
{
	int retval;

	TQ_LOCK(queue);
	retval = task->ta_pending > 0 || task_is_running(queue, task);
	TQ_UNLOCK(queue);

	return (retval);
}