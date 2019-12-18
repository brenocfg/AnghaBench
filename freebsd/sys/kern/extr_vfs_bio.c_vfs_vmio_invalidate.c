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
typedef  scalar_t__ vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct buf {int b_npages; int b_flags; int b_bufsize; int b_offset; scalar_t__* b_pages; TYPE_1__* b_bufobj; scalar_t__ b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  bo_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_CHECK_MAPPED (struct buf*) ; 
 int /*<<< orphan*/  BUF_CHECK_UNMAPPED (struct buf*) ; 
 int B_NOREUSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_ALLOC_SBUSY ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int VPR_NOREUSE ; 
 scalar_t__ bogus_page ; 
 scalar_t__ buf_mapped (struct buf*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pmap_page_wired_mappings (scalar_t__) ; 
 int /*<<< orphan*/  pmap_qremove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trunc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_busy_acquire (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_release_locked (scalar_t__,int) ; 
 int /*<<< orphan*/  vm_page_set_invalid (scalar_t__,int,int) ; 
 int /*<<< orphan*/  vm_page_sunbusy (scalar_t__) ; 

__attribute__((used)) static void
vfs_vmio_invalidate(struct buf *bp)
{
	vm_object_t obj;
	vm_page_t m;
	int flags, i, resid, poffset, presid;

	if (buf_mapped(bp)) {
		BUF_CHECK_MAPPED(bp);
		pmap_qremove(trunc_page((vm_offset_t)bp->b_data), bp->b_npages);
	} else
		BUF_CHECK_UNMAPPED(bp);
	/*
	 * Get the base offset and length of the buffer.  Note that 
	 * in the VMIO case if the buffer block size is not
	 * page-aligned then b_data pointer may not be page-aligned.
	 * But our b_pages[] array *IS* page aligned.
	 *
	 * block sizes less then DEV_BSIZE (usually 512) are not 
	 * supported due to the page granularity bits (m->valid,
	 * m->dirty, etc...). 
	 *
	 * See man buf(9) for more information
	 */
	flags = (bp->b_flags & B_NOREUSE) != 0 ? VPR_NOREUSE : 0;
	obj = bp->b_bufobj->bo_object;
	resid = bp->b_bufsize;
	poffset = bp->b_offset & PAGE_MASK;
	VM_OBJECT_WLOCK(obj);
	for (i = 0; i < bp->b_npages; i++) {
		m = bp->b_pages[i];
		if (m == bogus_page)
			panic("vfs_vmio_invalidate: Unexpected bogus page.");
		bp->b_pages[i] = NULL;

		presid = resid > (PAGE_SIZE - poffset) ?
		    (PAGE_SIZE - poffset) : resid;
		KASSERT(presid >= 0, ("brelse: extra page"));
		vm_page_busy_acquire(m, VM_ALLOC_SBUSY);
		if (pmap_page_wired_mappings(m) == 0)
			vm_page_set_invalid(m, poffset, presid);
		vm_page_sunbusy(m);
		vm_page_release_locked(m, flags);
		resid -= presid;
		poffset = 0;
	}
	VM_OBJECT_WUNLOCK(obj);
	bp->b_npages = 0;
}