#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ng_queue {int /*<<< orphan*/  q_flags; int /*<<< orphan*/  queue; } ;
typedef  TYPE_2__* node_p ;
typedef  TYPE_3__* item_p ;
struct TYPE_9__ {int depth; TYPE_1__* apply; } ;
struct TYPE_8__ {struct ng_queue nd_input_queue; } ;
struct TYPE_7__ {int /*<<< orphan*/  error; int /*<<< orphan*/  context; int /*<<< orphan*/  (* apply ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  NG_FREE_ITEM (TYPE_3__*) ; 
 int /*<<< orphan*/  NG_QUEUE_LOCK (struct ng_queue*) ; 
 int /*<<< orphan*/  NG_QUEUE_UNLOCK (struct ng_queue*) ; 
 int /*<<< orphan*/  OP_PENDING ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_3__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_clear_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_next ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_flush_input_queue(node_p node)
{
	struct ng_queue *ngq = &node->nd_input_queue;
	item_p item;

	NG_QUEUE_LOCK(ngq);
	while ((item = STAILQ_FIRST(&ngq->queue)) != NULL) {
		STAILQ_REMOVE_HEAD(&ngq->queue, el_next);
		if (STAILQ_EMPTY(&ngq->queue))
			atomic_clear_int(&ngq->q_flags, OP_PENDING);
		NG_QUEUE_UNLOCK(ngq);

		/* If the item is supplying a callback, call it with an error */
		if (item->apply != NULL) {
			if (item->depth == 1)
				item->apply->error = ENOENT;
			if (refcount_release(&item->apply->refs)) {
				(*item->apply->apply)(item->apply->context,
				    item->apply->error);
			}
		}
		NG_FREE_ITEM(item);
		NG_QUEUE_LOCK(ngq);
	}
	NG_QUEUE_UNLOCK(ngq);
}