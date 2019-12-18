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
struct taskqueue {struct task* tq_hint; int /*<<< orphan*/  tq_queue; } ;
struct task {int ta_pending; } ;

/* Variables and functions */
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (struct task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task*) ; 
 int /*<<< orphan*/  TQ_SLEEP (struct taskqueue*,struct task*,char*) ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  ta_link ; 
 int /*<<< orphan*/  taskqueue_task_nop_fn ; 

__attribute__((used)) static int
taskqueue_drain_tq_queue(struct taskqueue *queue)
{
	struct task t_barrier;

	if (STAILQ_EMPTY(&queue->tq_queue))
		return (0);

	/*
	 * Enqueue our barrier after all current tasks, but with
	 * the highest priority so that newly queued tasks cannot
	 * pass it.  Because of the high priority, we can not use
	 * taskqueue_enqueue_locked directly (which drops the lock
	 * anyway) so just insert it at tail while we have the
	 * queue lock.
	 */
	TASK_INIT(&t_barrier, USHRT_MAX, taskqueue_task_nop_fn, &t_barrier);
	STAILQ_INSERT_TAIL(&queue->tq_queue, &t_barrier, ta_link);
	queue->tq_hint = &t_barrier;
	t_barrier.ta_pending = 1;

	/*
	 * Once the barrier has executed, all previously queued tasks
	 * have completed or are currently executing.
	 */
	while (t_barrier.ta_pending != 0)
		TQ_SLEEP(queue, &t_barrier, "tq_qdrain");
	return (1);
}