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
struct binder_buffer {int dummy; } ;
struct binder_alloc {TYPE_1__* pages; } ;
struct TYPE_2__ {scalar_t__ page_ptr; int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int BUFFER_NUM ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  binder_alloc_free_buf (struct binder_alloc*,struct binder_buffer*) ; 
 int /*<<< orphan*/  binder_selftest_failures ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int) ; 
 int /*<<< orphan*/  pr_err_size_seq (size_t*,int*) ; 

__attribute__((used)) static void binder_selftest_free_buf(struct binder_alloc *alloc,
				     struct binder_buffer *buffers[],
				     size_t *sizes, int *seq, size_t end)
{
	int i;

	for (i = 0; i < BUFFER_NUM; i++)
		binder_alloc_free_buf(alloc, buffers[seq[i]]);

	for (i = 0; i < end / PAGE_SIZE; i++) {
		/**
		 * Error message on a free page can be false positive
		 * if binder shrinker ran during binder_alloc_free_buf
		 * calls above.
		 */
		if (list_empty(&alloc->pages[i].lru)) {
			pr_err_size_seq(sizes, seq);
			pr_err("expect lru but is %s at page index %d\n",
			       alloc->pages[i].page_ptr ? "alloc" : "free", i);
			binder_selftest_failures++;
		}
	}
}