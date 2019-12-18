#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bq_list; int /*<<< orphan*/  bq_lock; int /*<<< orphan*/  bq_pop_cv; int /*<<< orphan*/  bq_add_cv; int /*<<< orphan*/  bq_size; } ;
typedef  TYPE_1__ bqueue_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void
bqueue_destroy(bqueue_t *q)
{
	ASSERT0(q->bq_size);
	cv_destroy(&q->bq_add_cv);
	cv_destroy(&q->bq_pop_cv);
	mutex_destroy(&q->bq_lock);
	list_destroy(&q->bq_list);
}