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
 scalar_t__ IS_ERR (struct binder_buffer*) ; 
 struct binder_buffer* binder_alloc_new_buf (struct binder_alloc*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_selftest_failures ; 
 int /*<<< orphan*/  check_buffer_pages_allocated (struct binder_alloc*,struct binder_buffer*,size_t) ; 
 int /*<<< orphan*/  pr_err_size_seq (size_t*,int*) ; 

__attribute__((used)) static void binder_selftest_alloc_buf(struct binder_alloc *alloc,
				      struct binder_buffer *buffers[],
				      size_t *sizes, int *seq)
{
	int i;

	for (i = 0; i < BUFFER_NUM; i++) {
		buffers[i] = binder_alloc_new_buf(alloc, sizes[i], 0, 0, 0);
		if (IS_ERR(buffers[i]) ||
		    !check_buffer_pages_allocated(alloc, buffers[i],
						  sizes[i])) {
			pr_err_size_seq(sizes, seq);
			binder_selftest_failures++;
		}
	}
}