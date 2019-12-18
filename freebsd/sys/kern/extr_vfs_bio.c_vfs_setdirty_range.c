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
typedef  void* vm_offset_t ;
struct buf {int b_npages; int b_offset; void* b_bcount; void* b_dirtyoff; void* b_dirtyend; TYPE_1__** b_pages; } ;
struct TYPE_2__ {scalar_t__ dirty; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  vm_page_test_dirty (TYPE_1__*) ; 

__attribute__((used)) static void
vfs_setdirty_range(struct buf *bp)
{
	vm_offset_t boffset;
	vm_offset_t eoffset;
	int i;

	/*
	 * test the pages to see if they have been modified directly
	 * by users through the VM system.
	 */
	for (i = 0; i < bp->b_npages; i++)
		vm_page_test_dirty(bp->b_pages[i]);

	/*
	 * Calculate the encompassing dirty range, boffset and eoffset,
	 * (eoffset - boffset) bytes.
	 */

	for (i = 0; i < bp->b_npages; i++) {
		if (bp->b_pages[i]->dirty)
			break;
	}
	boffset = (i << PAGE_SHIFT) - (bp->b_offset & PAGE_MASK);

	for (i = bp->b_npages - 1; i >= 0; --i) {
		if (bp->b_pages[i]->dirty) {
			break;
		}
	}
	eoffset = ((i + 1) << PAGE_SHIFT) - (bp->b_offset & PAGE_MASK);

	/*
	 * Fit it to the buffer.
	 */

	if (eoffset > bp->b_bcount)
		eoffset = bp->b_bcount;

	/*
	 * If we have a good dirty range, merge with the existing
	 * dirty range.
	 */

	if (boffset < eoffset) {
		if (bp->b_dirtyoff > boffset)
			bp->b_dirtyoff = boffset;
		if (bp->b_dirtyend < eoffset)
			bp->b_dirtyend = eoffset;
	}
}