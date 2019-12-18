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
struct binder_buffer {int dummy; } ;
struct binder_alloc {int dummy; } ;

/* Variables and functions */
 int BUFFER_NUM ; 
 int /*<<< orphan*/  binder_alloc_lru ; 
 int /*<<< orphan*/  binder_selftest_alloc_buf (struct binder_alloc*,struct binder_buffer**,size_t*,int*) ; 
 int /*<<< orphan*/  binder_selftest_free_buf (struct binder_alloc*,struct binder_buffer**,size_t*,int*,size_t) ; 
 int /*<<< orphan*/  binder_selftest_free_page (struct binder_alloc*) ; 
 scalar_t__ list_lru_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void binder_selftest_alloc_free(struct binder_alloc *alloc,
				       size_t *sizes, int *seq, size_t end)
{
	struct binder_buffer *buffers[BUFFER_NUM];

	binder_selftest_alloc_buf(alloc, buffers, sizes, seq);
	binder_selftest_free_buf(alloc, buffers, sizes, seq, end);

	/* Allocate from lru. */
	binder_selftest_alloc_buf(alloc, buffers, sizes, seq);
	if (list_lru_count(&binder_alloc_lru))
		pr_err("lru list should be empty but is not\n");

	binder_selftest_free_buf(alloc, buffers, sizes, seq, end);
	binder_selftest_free_page(alloc);
}