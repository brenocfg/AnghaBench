#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct binder_alloc {int buffer_size; TYPE_1__* pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  lru; scalar_t__ page_ptr; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  binder_alloc_free_page ; 
 int /*<<< orphan*/  binder_alloc_lru ; 
 int /*<<< orphan*/  binder_selftest_failures ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 unsigned long list_lru_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int) ; 

__attribute__((used)) static void binder_selftest_free_page(struct binder_alloc *alloc)
{
	int i;
	unsigned long count;

	while ((count = list_lru_count(&binder_alloc_lru))) {
		list_lru_walk(&binder_alloc_lru, binder_alloc_free_page,
			      NULL, count);
	}

	for (i = 0; i < (alloc->buffer_size / PAGE_SIZE); i++) {
		if (alloc->pages[i].page_ptr) {
			pr_err("expect free but is %s at page index %d\n",
			       list_empty(&alloc->pages[i].lru) ?
			       "alloc" : "lru", i);
			binder_selftest_failures++;
		}
	}
}