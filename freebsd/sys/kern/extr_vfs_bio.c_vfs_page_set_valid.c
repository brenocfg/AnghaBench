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
struct buf {int b_offset; int b_bcount; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  vm_page_set_valid_range (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
vfs_page_set_valid(struct buf *bp, vm_ooffset_t off, vm_page_t m)
{
	vm_ooffset_t eoff;

	/*
	 * Compute the end offset, eoff, such that [off, eoff) does not span a
	 * page boundary and eoff is not greater than the end of the buffer.
	 * The end of the buffer, in this case, is our file EOF, not the
	 * allocation size of the buffer.
	 */
	eoff = (off + PAGE_SIZE) & ~(vm_ooffset_t)PAGE_MASK;
	if (eoff > bp->b_offset + bp->b_bcount)
		eoff = bp->b_offset + bp->b_bcount;

	/*
	 * Set valid range.  This is typically the entire buffer and thus the
	 * entire page.
	 */
	if (eoff > off)
		vm_page_set_valid_range(m, off & PAGE_MASK, eoff - off);
}