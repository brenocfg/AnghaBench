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
struct tsort_store {size_t alloc; void** storage; } ;

/* Variables and functions */
 void** git__reallocarray (void**,size_t,int) ; 

__attribute__((used)) static int resize(struct tsort_store *store, size_t new_size)
{
	if (store->alloc < new_size) {
		void **tempstore;

		tempstore = git__reallocarray(store->storage, new_size, sizeof(void *));

		/**
		 * Do not propagate on OOM; this will abort the sort and
		 * leave the array unsorted, but no error code will be
		 * raised
		 */
		if (tempstore == NULL)
			return -1;

		store->storage = tempstore;
		store->alloc = new_size;
	}

	return 0;
}