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
struct TYPE_2__ {int ta_pending; } ;
struct timeout_task {int f; int /*<<< orphan*/  c; TYPE_1__ t; struct taskqueue* q; } ;
struct taskqueue {int /*<<< orphan*/  tq_callouts; int /*<<< orphan*/  tq_spin; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int DT_CALLOUT_ARMED ; 
 int DT_DRAIN_IN_PROGRESS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeout_task*,int) ; 
 int /*<<< orphan*/  taskqueue_enqueue_locked (struct taskqueue*,TYPE_1__*) ; 
 int /*<<< orphan*/  taskqueue_timeout_func ; 

int
taskqueue_enqueue_timeout_sbt(struct taskqueue *queue,
    struct timeout_task *timeout_task, sbintime_t sbt, sbintime_t pr, int flags)
{
	int res;

	TQ_LOCK(queue);
	KASSERT(timeout_task->q == NULL || timeout_task->q == queue,
	    ("Migrated queue"));
	KASSERT(!queue->tq_spin, ("Timeout for spin-queue"));
	timeout_task->q = queue;
	res = timeout_task->t.ta_pending;
	if (timeout_task->f & DT_DRAIN_IN_PROGRESS) {
		/* Do nothing */
		TQ_UNLOCK(queue);
		res = -1;
	} else if (sbt == 0) {
		taskqueue_enqueue_locked(queue, &timeout_task->t);
		/* The lock is released inside. */
	} else {
		if ((timeout_task->f & DT_CALLOUT_ARMED) != 0) {
			res++;
		} else {
			queue->tq_callouts++;
			timeout_task->f |= DT_CALLOUT_ARMED;
			if (sbt < 0)
				sbt = -sbt; /* Ignore overflow. */
		}
		if (sbt > 0) {
			callout_reset_sbt(&timeout_task->c, sbt, pr,
			    taskqueue_timeout_func, timeout_task, flags);
		}
		TQ_UNLOCK(queue);
	}
	return (res);
}