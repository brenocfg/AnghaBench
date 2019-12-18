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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_ooffset_t ;
typedef  int vm_offset_t ;
struct buf {int b_flags; } ;

/* Variables and functions */
 int B_CACHE ; 
 int PAGE_MASK ; 
 scalar_t__ vm_page_is_valid (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static __inline void
vfs_buf_test_cache(struct buf *bp, vm_ooffset_t foff, vm_offset_t off,
    vm_offset_t size, vm_page_t m)
{

	/*
	 * This function and its results are protected by higher level
	 * synchronization requiring vnode and buf locks to page in and
	 * validate pages.
	 */
	if (bp->b_flags & B_CACHE) {
		int base = (foff + off) & PAGE_MASK;
		if (vm_page_is_valid(m, base, size) == 0)
			bp->b_flags &= ~B_CACHE;
	}
}