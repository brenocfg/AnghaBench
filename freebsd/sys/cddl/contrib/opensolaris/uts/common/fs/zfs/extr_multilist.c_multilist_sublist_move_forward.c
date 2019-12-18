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
struct TYPE_3__ {int /*<<< orphan*/  mls_list; int /*<<< orphan*/  mls_lock; } ;
typedef  TYPE_1__ multilist_sublist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_insert_before (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ *) ; 
 void* list_prev (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,void*) ; 

void
multilist_sublist_move_forward(multilist_sublist_t *mls, void *obj)
{
	void *prev = list_prev(&mls->mls_list, obj);

	ASSERT(MUTEX_HELD(&mls->mls_lock));
	ASSERT(!list_is_empty(&mls->mls_list));

	/* 'obj' must be at the head of the list, nothing to do */
	if (prev == NULL)
		return;

	list_remove(&mls->mls_list, obj);
	list_insert_before(&mls->mls_list, prev, obj);
}