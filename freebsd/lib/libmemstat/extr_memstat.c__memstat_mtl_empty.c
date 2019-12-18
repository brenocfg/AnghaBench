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
struct memory_type_list {int /*<<< orphan*/  mtl_list; } ;
struct memory_type {struct memory_type* mt_percpu_cache; struct memory_type* mt_percpu_alloc; } ;

/* Variables and functions */
 struct memory_type* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct memory_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct memory_type*) ; 
 int /*<<< orphan*/  mt_list ; 

void
_memstat_mtl_empty(struct memory_type_list *list)
{
	struct memory_type *mtp;

	while ((mtp = LIST_FIRST(&list->mtl_list))) {
		free(mtp->mt_percpu_alloc);
		free(mtp->mt_percpu_cache);
		LIST_REMOVE(mtp, mt_list);
		free(mtp);
	}
}