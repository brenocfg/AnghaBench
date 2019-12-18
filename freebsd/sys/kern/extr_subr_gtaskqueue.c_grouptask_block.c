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
struct gtaskqueue {int dummy; } ;
struct gtask {int /*<<< orphan*/  ta_flags; } ;
struct grouptask {struct gtask gt_task; struct gtaskqueue* gt_taskqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NOENQUEUE ; 
 int /*<<< orphan*/  TQ_LOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  gtask_dump (struct gtask*) ; 
 int /*<<< orphan*/  gtaskqueue_drain_locked (struct gtaskqueue*,struct gtask*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
grouptask_block(struct grouptask *grouptask)
{
	struct gtaskqueue *queue = grouptask->gt_taskqueue;
	struct gtask *gtask = &grouptask->gt_task;

#ifdef INVARIANTS
	if (queue == NULL) {
		gtask_dump(gtask);
		panic("queue == NULL");
	}
#endif
	TQ_LOCK(queue);
	gtask->ta_flags |= TASK_NOENQUEUE;
  	gtaskqueue_drain_locked(queue, gtask);
	TQ_UNLOCK(queue);
}