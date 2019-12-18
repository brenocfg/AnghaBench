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
struct taskqueue {int /*<<< orphan*/  tq_context; int /*<<< orphan*/  (* tq_enqueue ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  tq_queue; int /*<<< orphan*/  tq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TQ_FLAGS_BLOCKED ; 
 int /*<<< orphan*/  TQ_LOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  TQ_UNLOCK (struct taskqueue*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
taskqueue_unblock(struct taskqueue *queue)
{

	TQ_LOCK(queue);
	queue->tq_flags &= ~TQ_FLAGS_BLOCKED;
	if (!STAILQ_EMPTY(&queue->tq_queue))
		queue->tq_enqueue(queue->tq_context);
	TQ_UNLOCK(queue);
}