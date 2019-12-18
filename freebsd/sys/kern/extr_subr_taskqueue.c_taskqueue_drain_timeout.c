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
struct timeout_task {int f; int /*<<< orphan*/  t; int /*<<< orphan*/  c; } ;
struct taskqueue {int dummy; } ;

/* Variables and functions */
 int DT_DRAIN_IN_PROGRESS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (struct taskqueue*,int /*<<< orphan*/ *) ; 

void
taskqueue_drain_timeout(struct taskqueue *queue,
    struct timeout_task *timeout_task)
{

	/*
	 * Set flag to prevent timer from re-starting during drain:
	 */
	TQ_LOCK(queue);
	KASSERT((timeout_task->f & DT_DRAIN_IN_PROGRESS) == 0,
	    ("Drain already in progress"));
	timeout_task->f |= DT_DRAIN_IN_PROGRESS;
	TQ_UNLOCK(queue);

	callout_drain(&timeout_task->c);
	taskqueue_drain(queue, &timeout_task->t);

	/*
	 * Clear flag to allow timer to re-start:
	 */
	TQ_LOCK(queue);
	timeout_task->f &= ~DT_DRAIN_IN_PROGRESS;
	TQ_UNLOCK(queue);
}