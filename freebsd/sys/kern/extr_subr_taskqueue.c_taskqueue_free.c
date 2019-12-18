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
struct taskqueue {scalar_t__ tq_callouts; struct taskqueue* tq_name; struct taskqueue* tq_threads; int /*<<< orphan*/  tq_mutex; int /*<<< orphan*/  tq_active; int /*<<< orphan*/  tq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_TASKQUEUE ; 
 int /*<<< orphan*/  TQ_FLAGS_ACTIVE ; 
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  free (struct taskqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_terminate (struct taskqueue*,struct taskqueue*) ; 

void
taskqueue_free(struct taskqueue *queue)
{

	TQ_LOCK(queue);
	queue->tq_flags &= ~TQ_FLAGS_ACTIVE;
	taskqueue_terminate(queue->tq_threads, queue);
	KASSERT(LIST_EMPTY(&queue->tq_active), ("Tasks still running?"));
	KASSERT(queue->tq_callouts == 0, ("Armed timeout tasks"));
	mtx_destroy(&queue->tq_mutex);
	free(queue->tq_threads, M_TASKQUEUE);
	free(queue->tq_name, M_TASKQUEUE);
	free(queue, M_TASKQUEUE);
}