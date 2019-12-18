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
 int EBUSY ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct gtask*,struct gtask*,int /*<<< orphan*/ ) ; 
 int TASK_ENQUEUED ; 
 int /*<<< orphan*/  ta_link ; 
 scalar_t__ task_is_running (struct gtaskqueue*,struct gtask*) ; 

__attribute__((used)) static int
gtaskqueue_cancel_locked(struct gtaskqueue *queue, struct gtask *gtask)
{

	if (gtask->ta_flags & TASK_ENQUEUED)
		STAILQ_REMOVE(&queue->tq_queue, gtask, gtask, ta_link);
	gtask->ta_flags &= ~TASK_ENQUEUED;
	return (task_is_running(queue, gtask) ? EBUSY : 0);
}