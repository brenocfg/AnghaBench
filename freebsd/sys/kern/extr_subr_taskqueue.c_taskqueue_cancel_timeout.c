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
typedef  int u_int ;
struct timeout_task {int f; int /*<<< orphan*/  t; int /*<<< orphan*/  c; } ;
struct taskqueue {int /*<<< orphan*/  tq_callouts; } ;

/* Variables and functions */
 int DT_CALLOUT_ARMED ; 
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 scalar_t__ callout_stop (int /*<<< orphan*/ *) ; 
 int taskqueue_cancel_locked (struct taskqueue*,int /*<<< orphan*/ *,int*) ; 

int
taskqueue_cancel_timeout(struct taskqueue *queue,
    struct timeout_task *timeout_task, u_int *pendp)
{
	u_int pending, pending1;
	int error;

	TQ_LOCK(queue);
	pending = !!(callout_stop(&timeout_task->c) > 0);
	error = taskqueue_cancel_locked(queue, &timeout_task->t, &pending1);
	if ((timeout_task->f & DT_CALLOUT_ARMED) != 0) {
		timeout_task->f &= ~DT_CALLOUT_ARMED;
		queue->tq_callouts--;
	}
	TQ_UNLOCK(queue);

	if (pendp != NULL)
		*pendp = pending + pending1;
	return (error);
}