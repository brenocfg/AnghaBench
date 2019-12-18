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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct buf {int b_flags; int b_offset; int b_npages; scalar_t__ b_bufsize; int /*<<< orphan*/ * b_pages; scalar_t__ b_data; TYPE_1__* b_bufobj; } ;
typedef  int off_t ;
struct TYPE_2__ {int /*<<< orphan*/  bo_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_CHECK_MAPPED (struct buf*) ; 
 int B_CACHE ; 
 int B_CLUSTER ; 
 int B_VMIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NOOFFSET ; 
 scalar_t__ PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bogus_page ; 
 scalar_t__ buf_mapped (struct buf*) ; 
 int /*<<< orphan*/  pmap_qenter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmap_remove_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_busy_pages_acquire (struct buf*) ; 
 int /*<<< orphan*/  vfs_page_set_validclean (struct buf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_setdirty_range (struct buf*) ; 
 int /*<<< orphan*/  vm_object_pip_add (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vm_page_all_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_assert_sbusied (int /*<<< orphan*/ ) ; 

void
vfs_busy_pages(struct buf *bp, int clear_modify)
{
	vm_object_t obj;
	vm_ooffset_t foff;
	vm_page_t m;
	int i;
	bool bogus;

	if (!(bp->b_flags & B_VMIO))
		return;

	obj = bp->b_bufobj->bo_object;
	foff = bp->b_offset;
	KASSERT(bp->b_offset != NOOFFSET,
	    ("vfs_busy_pages: no buffer offset"));
	if ((bp->b_flags & B_CLUSTER) == 0) {
		vm_object_pip_add(obj, bp->b_npages);
		vfs_busy_pages_acquire(bp);
	}
	if (bp->b_bufsize != 0)
		vfs_setdirty_range(bp);
	bogus = false;
	for (i = 0; i < bp->b_npages; i++) {
		m = bp->b_pages[i];
		vm_page_assert_sbusied(m);

		/*
		 * When readying a buffer for a read ( i.e
		 * clear_modify == 0 ), it is important to do
		 * bogus_page replacement for valid pages in 
		 * partially instantiated buffers.  Partially 
		 * instantiated buffers can, in turn, occur when
		 * reconstituting a buffer from its VM backing store
		 * base.  We only have to do this if B_CACHE is
		 * clear ( which causes the I/O to occur in the
		 * first place ).  The replacement prevents the read
		 * I/O from overwriting potentially dirty VM-backed
		 * pages.  XXX bogus page replacement is, uh, bogus.
		 * It may not work properly with small-block devices.
		 * We need to find a better way.
		 */
		if (clear_modify) {
			pmap_remove_write(m);
			vfs_page_set_validclean(bp, foff, m);
		} else if (vm_page_all_valid(m) &&
		    (bp->b_flags & B_CACHE) == 0) {
			bp->b_pages[i] = bogus_page;
			bogus = true;
		}
		foff = (foff + PAGE_SIZE) & ~(off_t)PAGE_MASK;
	}
	if (bogus && buf_mapped(bp)) {
		BUF_CHECK_MAPPED(bp);
		pmap_qenter(trunc_page((vm_offset_t)bp->b_data),
		    bp->b_pages, bp->b_npages);
	}
}