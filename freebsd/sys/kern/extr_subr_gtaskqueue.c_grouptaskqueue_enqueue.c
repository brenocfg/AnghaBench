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
struct gtaskqueue {int tq_flags; int /*<<< orphan*/  tq_context; int /*<<< orphan*/  (* tq_enqueue ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  tq_queue; } ;
struct gtask {int ta_flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gtask*,int /*<<< orphan*/ ) ; 
 int TASK_ENQUEUED ; 
 int TASK_NOENQUEUE ; 
 int TQ_FLAGS_BLOCKED ; 
 int /*<<< orphan*/  TQ_LOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  gtask_dump (struct gtask*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ta_link ; 

int
grouptaskqueue_enqueue(struct gtaskqueue *queue, struct gtask *gtask)
{
#ifdef INVARIANTS
	if (queue == NULL) {
		gtask_dump(gtask);
		panic("queue == NULL");
	}
#endif
	TQ_LOCK(queue);
	if (gtask->ta_flags & TASK_ENQUEUED) {
		TQ_UNLOCK(queue);
		return (0);
	}
	if (gtask->ta_flags & TASK_NOENQUEUE) {
		TQ_UNLOCK(queue);
		return (EAGAIN);
	}
	STAILQ_INSERT_TAIL(&queue->tq_queue, gtask, ta_link);
	gtask->ta_flags |= TASK_ENQUEUED;
	TQ_UNLOCK(queue);
	if ((queue->tq_flags & TQ_FLAGS_BLOCKED) == 0)
		queue->tq_enqueue(queue->tq_context);
	return (0);
}