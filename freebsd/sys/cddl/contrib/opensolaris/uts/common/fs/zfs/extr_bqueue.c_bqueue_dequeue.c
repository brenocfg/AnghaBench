#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ bq_size; int /*<<< orphan*/  bq_add_cv; int /*<<< orphan*/  bq_lock; int /*<<< orphan*/  bq_list; int /*<<< orphan*/  bq_pop_cv; } ;
typedef  TYPE_1__ bqueue_t ;
struct TYPE_6__ {scalar_t__ bqn_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_2__* obj2node (TYPE_1__*,void*) ; 

void *
bqueue_dequeue(bqueue_t *q)
{
	void *ret;
	uint64_t item_size;
	mutex_enter(&q->bq_lock);
	while (q->bq_size == 0) {
		cv_wait(&q->bq_pop_cv, &q->bq_lock);
	}
	ret = list_remove_head(&q->bq_list);
	item_size = obj2node(q, ret)->bqn_size;
	q->bq_size -= item_size;
	mutex_exit(&q->bq_lock);
	cv_signal(&q->bq_add_cv);
	return (ret);
}