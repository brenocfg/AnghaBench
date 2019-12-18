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
struct taskqueue {int tq_flags; int /*<<< orphan*/  tq_context; int /*<<< orphan*/  (* tq_enqueue ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  tq_queue; struct task* tq_hint; } ;
struct task {int ta_pending; scalar_t__ ta_priority; int /*<<< orphan*/ * ta_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct task* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct task*,struct task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct task*,int /*<<< orphan*/ ) ; 
 struct task* STAILQ_LAST (int /*<<< orphan*/ *,struct task*,int /*<<< orphan*/ ) ; 
 struct task* STAILQ_NEXT (struct task*,int /*<<< orphan*/ ) ; 
 int TQ_FLAGS_BLOCKED ; 
 int TQ_FLAGS_UNLOCKED_ENQUEUE ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 int USHRT_MAX ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ta_link ; 

__attribute__((used)) static int
taskqueue_enqueue_locked(struct taskqueue *queue, struct task *task)
{
	struct task *ins;
	struct task *prev;

	KASSERT(task->ta_func != NULL, ("enqueueing task with NULL func"));
	/*
	 * Count multiple enqueues.
	 */
	if (task->ta_pending) {
		if (task->ta_pending < USHRT_MAX)
			task->ta_pending++;
		TQ_UNLOCK(queue);
		return (0);
	}

	/*
	 * Optimise cases when all tasks use small set of priorities.
	 * In case of only one priority we always insert at the end.
	 * In case of two tq_hint typically gives the insertion point.
	 * In case of more then two tq_hint should halve the search.
	 */
	prev = STAILQ_LAST(&queue->tq_queue, task, ta_link);
	if (!prev || prev->ta_priority >= task->ta_priority) {
		STAILQ_INSERT_TAIL(&queue->tq_queue, task, ta_link);
	} else {
		prev = queue->tq_hint;
		if (prev && prev->ta_priority >= task->ta_priority) {
			ins = STAILQ_NEXT(prev, ta_link);
		} else {
			prev = NULL;
			ins = STAILQ_FIRST(&queue->tq_queue);
		}
		for (; ins; prev = ins, ins = STAILQ_NEXT(ins, ta_link))
			if (ins->ta_priority < task->ta_priority)
				break;

		if (prev) {
			STAILQ_INSERT_AFTER(&queue->tq_queue, prev, task, ta_link);
			queue->tq_hint = task;
		} else
			STAILQ_INSERT_HEAD(&queue->tq_queue, task, ta_link);
	}

	task->ta_pending = 1;
	if ((queue->tq_flags & TQ_FLAGS_UNLOCKED_ENQUEUE) != 0)
		TQ_UNLOCK(queue);
	if ((queue->tq_flags & TQ_FLAGS_BLOCKED) == 0)
		queue->tq_enqueue(queue->tq_context);
	if ((queue->tq_flags & TQ_FLAGS_UNLOCKED_ENQUEUE) == 0)
		TQ_UNLOCK(queue);

	/* Return with lock released. */
	return (0);
}