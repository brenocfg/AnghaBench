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
struct buf {int b_flags; int b_bufsize; int b_offset; int b_npages; int /*<<< orphan*/ * b_pages; } ;
typedef  int off_t ;

/* Variables and functions */
 int B_VMIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NOOFFSET ; 
 scalar_t__ PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  vfs_busy_pages_acquire (struct buf*) ; 
 int /*<<< orphan*/  vfs_busy_pages_release (struct buf*) ; 
 int /*<<< orphan*/  vfs_page_set_validclean (struct buf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_setdirty_range (struct buf*) ; 

__attribute__((used)) static void
vfs_clean_pages_dirty_buf(struct buf *bp)
{
	vm_ooffset_t foff, noff, eoff;
	vm_page_t m;
	int i;

	if ((bp->b_flags & B_VMIO) == 0 || bp->b_bufsize == 0)
		return;

	foff = bp->b_offset;
	KASSERT(bp->b_offset != NOOFFSET,
	    ("vfs_clean_pages_dirty_buf: no buffer offset"));

	vfs_busy_pages_acquire(bp);
	vfs_setdirty_range(bp);
	for (i = 0; i < bp->b_npages; i++) {
		noff = (foff + PAGE_SIZE) & ~(off_t)PAGE_MASK;
		eoff = noff;
		if (eoff > bp->b_offset + bp->b_bufsize)
			eoff = bp->b_offset + bp->b_bufsize;
		m = bp->b_pages[i];
		vfs_page_set_validclean(bp, foff, m);
		/* vm_page_clear_dirty(m, foff & PAGE_MASK, eoff - foff); */
		foff = noff;
	}
	vfs_busy_pages_release(bp);
}