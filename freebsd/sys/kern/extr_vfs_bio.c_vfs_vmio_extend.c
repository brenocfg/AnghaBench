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
typedef  size_t vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct buf {int b_npages; int b_offset; int b_bcount; int b_flags; int /*<<< orphan*/ * b_pages; TYPE_1__* b_bufobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  bo_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_CHECK_UNMAPPED (struct buf*) ; 
 int B_CACHE ; 
 scalar_t__ OFF_TO_IDX (int) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int VM_ALLOC_IGN_SBUSY ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_SYSTEM ; 
 int VM_ALLOC_WIRED ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpmap_qenter (struct buf*) ; 
 scalar_t__ buf_mapped (struct buf*) ; 
 int /*<<< orphan*/  vfs_buf_test_cache (struct buf*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_grab_pages (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
vfs_vmio_extend(struct buf *bp, int desiredpages, int size)
{
	/*
	 * We are growing the buffer, possibly in a 
	 * byte-granular fashion.
	 */
	vm_object_t obj;
	vm_offset_t toff;
	vm_offset_t tinc;
	vm_page_t m;

	/*
	 * Step 1, bring in the VM pages from the object, allocating
	 * them if necessary.  We must clear B_CACHE if these pages
	 * are not valid for the range covered by the buffer.
	 */
	obj = bp->b_bufobj->bo_object;
	if (bp->b_npages < desiredpages) {
		/*
		 * We must allocate system pages since blocking
		 * here could interfere with paging I/O, no
		 * matter which process we are.
		 *
		 * Only exclusive busy can be tested here.
		 * Blocking on shared busy might lead to
		 * deadlocks once allocbuf() is called after
		 * pages are vfs_busy_pages().
		 */
		VM_OBJECT_WLOCK(obj);
		(void)vm_page_grab_pages(obj,
		    OFF_TO_IDX(bp->b_offset) + bp->b_npages,
		    VM_ALLOC_SYSTEM | VM_ALLOC_IGN_SBUSY |
		    VM_ALLOC_NOBUSY | VM_ALLOC_WIRED,
		    &bp->b_pages[bp->b_npages], desiredpages - bp->b_npages);
		VM_OBJECT_WUNLOCK(obj);
		bp->b_npages = desiredpages;
	}

	/*
	 * Step 2.  We've loaded the pages into the buffer,
	 * we have to figure out if we can still have B_CACHE
	 * set.  Note that B_CACHE is set according to the
	 * byte-granular range ( bcount and size ), not the
	 * aligned range ( newbsize ).
	 *
	 * The VM test is against m->valid, which is DEV_BSIZE
	 * aligned.  Needless to say, the validity of the data
	 * needs to also be DEV_BSIZE aligned.  Note that this
	 * fails with NFS if the server or some other client
	 * extends the file's EOF.  If our buffer is resized, 
	 * B_CACHE may remain set! XXX
	 */
	toff = bp->b_bcount;
	tinc = PAGE_SIZE - ((bp->b_offset + toff) & PAGE_MASK);
	while ((bp->b_flags & B_CACHE) && toff < size) {
		vm_pindex_t pi;

		if (tinc > (size - toff))
			tinc = size - toff;
		pi = ((bp->b_offset & PAGE_MASK) + toff) >> PAGE_SHIFT;
		m = bp->b_pages[pi];
		vfs_buf_test_cache(bp, bp->b_offset, toff, tinc, m);
		toff += tinc;
		tinc = PAGE_SIZE;
	}

	/*
	 * Step 3, fixup the KVA pmap.
	 */
	if (buf_mapped(bp))
		bpmap_qenter(bp);
	else
		BUF_CHECK_UNMAPPED(bp);
}