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
struct gtaskqueue_busy {scalar_t__ tb_seq; struct gtask* tb_running; } ;
struct gtaskqueue {scalar_t__ tq_seq; int /*<<< orphan*/  tq_queue; int /*<<< orphan*/  tq_active; } ;
struct gtask {int /*<<< orphan*/  ta_context; int /*<<< orphan*/  (* ta_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  ta_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct gtaskqueue_busy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct gtaskqueue_busy*,int /*<<< orphan*/ ) ; 
 struct gtask* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_ENQUEUED ; 
 int /*<<< orphan*/  TQ_ASSERT_LOCKED (struct gtaskqueue*) ; 
 int /*<<< orphan*/  TQ_LOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct gtaskqueue*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ta_link ; 
 int /*<<< orphan*/  tb_link ; 
 int /*<<< orphan*/  wakeup (struct gtask*) ; 

__attribute__((used)) static void
gtaskqueue_run_locked(struct gtaskqueue *queue)
{
	struct gtaskqueue_busy tb;
	struct gtask *gtask;

	KASSERT(queue != NULL, ("tq is NULL"));
	TQ_ASSERT_LOCKED(queue);
	tb.tb_running = NULL;
	LIST_INSERT_HEAD(&queue->tq_active, &tb, tb_link);

	while ((gtask = STAILQ_FIRST(&queue->tq_queue)) != NULL) {
		STAILQ_REMOVE_HEAD(&queue->tq_queue, ta_link);
		gtask->ta_flags &= ~TASK_ENQUEUED;
		tb.tb_running = gtask;
		tb.tb_seq = ++queue->tq_seq;
		TQ_UNLOCK(queue);

		KASSERT(gtask->ta_func != NULL, ("task->ta_func is NULL"));
		gtask->ta_func(gtask->ta_context);

		TQ_LOCK(queue);
		wakeup(gtask);
	}
	LIST_REMOVE(&tb, tb_link);
}