#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _ck_array {int length; int /*<<< orphan*/  n_committed; } ;
struct TYPE_5__ {int /*<<< orphan*/  n_entries; struct _ck_array* active; struct _ck_array* transaction; TYPE_1__* allocator; } ;
typedef  TYPE_2__ ck_array_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* free ) (struct _ck_array*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ck_pr_fence_store () ; 
 int /*<<< orphan*/  ck_pr_store_ptr (struct _ck_array**,struct _ck_array*) ; 
 int /*<<< orphan*/  ck_pr_store_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct _ck_array*,int,int) ; 

bool
ck_array_commit(ck_array_t *array)
{
	struct _ck_array *m = array->transaction;

	if (m != NULL) {
		struct _ck_array *p;

		m->n_committed = array->n_entries;
		ck_pr_fence_store();
		p = array->active;
		ck_pr_store_ptr(&array->active, m);
		array->allocator->free(p, sizeof(struct _ck_array) +
		    p->length * sizeof(void *), true);
		array->transaction = NULL;

		return true;
	}

	ck_pr_fence_store();
	ck_pr_store_uint(&array->active->n_committed, array->n_entries);
	return true;
}