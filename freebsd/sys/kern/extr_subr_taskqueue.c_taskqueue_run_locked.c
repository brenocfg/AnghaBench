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
struct taskqueue_busy {scalar_t__ tb_seq; struct task* tb_running; } ;
struct taskqueue {scalar_t__ tq_seq; struct task* tq_hint; int /*<<< orphan*/  tq_queue; int /*<<< orphan*/  tq_active; } ;
struct task {int ta_pending; int /*<<< orphan*/  ta_context; int /*<<< orphan*/  (* ta_func ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct taskqueue_busy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct taskqueue_busy*,int /*<<< orphan*/ ) ; 
 struct task* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TQ_ASSERT_LOCKED (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ta_link ; 
 int /*<<< orphan*/  tb_link ; 
 int /*<<< orphan*/  wakeup (struct task*) ; 

__attribute__((used)) static void
taskqueue_run_locked(struct taskqueue *queue)
{
	struct taskqueue_busy tb;
	struct task *task;
	int pending;

	KASSERT(queue != NULL, ("tq is NULL"));
	TQ_ASSERT_LOCKED(queue);
	tb.tb_running = NULL;
	LIST_INSERT_HEAD(&queue->tq_active, &tb, tb_link);

	while ((task = STAILQ_FIRST(&queue->tq_queue)) != NULL) {
		STAILQ_REMOVE_HEAD(&queue->tq_queue, ta_link);
		if (queue->tq_hint == task)
			queue->tq_hint = NULL;
		pending = task->ta_pending;
		task->ta_pending = 0;
		tb.tb_running = task;
		tb.tb_seq = ++queue->tq_seq;
		TQ_UNLOCK(queue);

		KASSERT(task->ta_func != NULL, ("task->ta_func is NULL"));
		task->ta_func(task->ta_context, pending);

		TQ_LOCK(queue);
		wakeup(task);
	}
	LIST_REMOVE(&tb, tb_link);
}