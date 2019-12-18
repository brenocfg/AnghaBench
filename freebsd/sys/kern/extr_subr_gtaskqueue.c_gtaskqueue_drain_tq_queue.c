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
struct gtaskqueue {int /*<<< orphan*/  tq_queue; } ;
struct gtask {int ta_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTASK_INIT (struct gtask*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gtask*) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gtask*,int /*<<< orphan*/ ) ; 
 int TASK_ENQUEUED ; 
 int /*<<< orphan*/  TQ_SLEEP (struct gtaskqueue*,struct gtask*,char*) ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  gtaskqueue_task_nop_fn ; 
 int /*<<< orphan*/  ta_link ; 

__attribute__((used)) static void
gtaskqueue_drain_tq_queue(struct gtaskqueue *queue)
{
	struct gtask t_barrier;

	if (STAILQ_EMPTY(&queue->tq_queue))
		return;

	/*
	 * Enqueue our barrier after all current tasks, but with
	 * the highest priority so that newly queued tasks cannot
	 * pass it.  Because of the high priority, we can not use
	 * taskqueue_enqueue_locked directly (which drops the lock
	 * anyway) so just insert it at tail while we have the
	 * queue lock.
	 */
	GTASK_INIT(&t_barrier, 0, USHRT_MAX, gtaskqueue_task_nop_fn, &t_barrier);
	STAILQ_INSERT_TAIL(&queue->tq_queue, &t_barrier, ta_link);
	t_barrier.ta_flags |= TASK_ENQUEUED;

	/*
	 * Once the barrier has executed, all previously queued tasks
	 * have completed or are currently executing.
	 */
	while (t_barrier.ta_flags & TASK_ENQUEUED)
		TQ_SLEEP(queue, &t_barrier, "gtq_qdrain");
}