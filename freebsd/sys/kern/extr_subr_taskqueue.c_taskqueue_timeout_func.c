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
struct timeout_task {int f; int /*<<< orphan*/  t; struct taskqueue* q; } ;
struct taskqueue {int /*<<< orphan*/  tq_callouts; } ;

/* Variables and functions */
 int DT_CALLOUT_ARMED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  taskqueue_enqueue_locked (struct taskqueue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
taskqueue_timeout_func(void *arg)
{
	struct taskqueue *queue;
	struct timeout_task *timeout_task;

	timeout_task = arg;
	queue = timeout_task->q;
	KASSERT((timeout_task->f & DT_CALLOUT_ARMED) != 0, ("Stray timeout"));
	timeout_task->f &= ~DT_CALLOUT_ARMED;
	queue->tq_callouts--;
	taskqueue_enqueue_locked(timeout_task->q, &timeout_task->t);
	/* The lock is released inside. */
}