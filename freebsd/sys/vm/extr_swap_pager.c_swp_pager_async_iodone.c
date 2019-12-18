#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_2__* vm_object_t ;
struct buf {int b_ioflags; scalar_t__ b_error; scalar_t__ b_iocmd; int b_npages; int b_pgbefore; int b_pgafter; int b_flags; int /*<<< orphan*/ * b_bufobj; int /*<<< orphan*/ * b_vp; TYPE_1__** b_pages; scalar_t__ b_kvabase; scalar_t__ b_data; scalar_t__ b_bcount; scalar_t__ b_blkno; } ;
struct TYPE_18__ {int handle; } ;
struct TYPE_17__ {int oflags; scalar_t__ dirty; TYPE_2__* object; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 scalar_t__ BIO_READ ; 
 int B_ASYNC ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 int VPO_SWAPINPROG ; 
 int VPO_SWAPSLEEP ; 
 scalar_t__ buf_mapped (struct buf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nsw_wcount_async ; 
 int /*<<< orphan*/  pmap_page_is_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_page_is_write_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_qremove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,long,long,scalar_t__) ; 
 int /*<<< orphan*/  swbuf_mtx ; 
 int /*<<< orphan*/  swrbuf_zone ; 
 int /*<<< orphan*/  swwbuf_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct buf*) ; 
 int /*<<< orphan*/  vm_object_pip_wakeupn (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_page_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_deactivate_noreuse (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_invalid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_readahead_finish (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_sunbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_undirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
swp_pager_async_iodone(struct buf *bp)
{
	int i;
	vm_object_t object = NULL;

	/*
	 * Report error - unless we ran out of memory, in which case
	 * we've already logged it in swapgeom_strategy().
	 */
	if (bp->b_ioflags & BIO_ERROR && bp->b_error != ENOMEM) {
		printf(
		    "swap_pager: I/O error - %s failed; blkno %ld,"
			"size %ld, error %d\n",
		    ((bp->b_iocmd == BIO_READ) ? "pagein" : "pageout"),
		    (long)bp->b_blkno,
		    (long)bp->b_bcount,
		    bp->b_error
		);
	}

	/*
	 * remove the mapping for kernel virtual
	 */
	if (buf_mapped(bp))
		pmap_qremove((vm_offset_t)bp->b_data, bp->b_npages);
	else
		bp->b_data = bp->b_kvabase;

	if (bp->b_npages) {
		object = bp->b_pages[0]->object;
		VM_OBJECT_WLOCK(object);
	}

	/*
	 * cleanup pages.  If an error occurs writing to swap, we are in
	 * very serious trouble.  If it happens to be a disk error, though,
	 * we may be able to recover by reassigning the swap later on.  So
	 * in this case we remove the m->swapblk assignment for the page
	 * but do not free it in the rlist.  The errornous block(s) are thus
	 * never reallocated as swap.  Redirty the page and continue.
	 */
	for (i = 0; i < bp->b_npages; ++i) {
		vm_page_t m = bp->b_pages[i];

		m->oflags &= ~VPO_SWAPINPROG;
		if (m->oflags & VPO_SWAPSLEEP) {
			m->oflags &= ~VPO_SWAPSLEEP;
			wakeup(&object->handle);
		}

		if (bp->b_ioflags & BIO_ERROR) {
			/*
			 * If an error occurs I'd love to throw the swapblk
			 * away without freeing it back to swapspace, so it
			 * can never be used again.  But I can't from an
			 * interrupt.
			 */
			if (bp->b_iocmd == BIO_READ) {
				/*
				 * NOTE: for reads, m->dirty will probably
				 * be overridden by the original caller of
				 * getpages so don't play cute tricks here.
				 */
				vm_page_invalid(m);
			} else {
				/*
				 * If a write error occurs, reactivate page
				 * so it doesn't clog the inactive list,
				 * then finish the I/O.
				 */
				MPASS(m->dirty == VM_PAGE_BITS_ALL);
				vm_page_lock(m);
				vm_page_activate(m);
				vm_page_unlock(m);
				vm_page_sunbusy(m);
			}
		} else if (bp->b_iocmd == BIO_READ) {
			/*
			 * NOTE: for reads, m->dirty will probably be
			 * overridden by the original caller of getpages so
			 * we cannot set them in order to free the underlying
			 * swap in a low-swap situation.  I don't think we'd
			 * want to do that anyway, but it was an optimization
			 * that existed in the old swapper for a time before
			 * it got ripped out due to precisely this problem.
			 */
			KASSERT(!pmap_page_is_mapped(m),
			    ("swp_pager_async_iodone: page %p is mapped", m));
			KASSERT(m->dirty == 0,
			    ("swp_pager_async_iodone: page %p is dirty", m));

			vm_page_valid(m);
			if (i < bp->b_pgbefore ||
			    i >= bp->b_npages - bp->b_pgafter)
				vm_page_readahead_finish(m);
		} else {
			/*
			 * For write success, clear the dirty
			 * status, then finish the I/O ( which decrements the
			 * busy count and possibly wakes waiter's up ).
			 * A page is only written to swap after a period of
			 * inactivity.  Therefore, we do not expect it to be
			 * reused.
			 */
			KASSERT(!pmap_page_is_write_mapped(m),
			    ("swp_pager_async_iodone: page %p is not write"
			    " protected", m));
			vm_page_undirty(m);
			vm_page_lock(m);
			vm_page_deactivate_noreuse(m);
			vm_page_unlock(m);
			vm_page_sunbusy(m);
		}
	}

	/*
	 * adjust pip.  NOTE: the original parent may still have its own
	 * pip refs on the object.
	 */
	if (object != NULL) {
		vm_object_pip_wakeupn(object, bp->b_npages);
		VM_OBJECT_WUNLOCK(object);
	}

	/*
	 * swapdev_strategy() manually sets b_vp and b_bufobj before calling
	 * bstrategy(). Set them back to NULL now we're done with it, or we'll
	 * trigger a KASSERT in relpbuf().
	 */
	if (bp->b_vp) {
		    bp->b_vp = NULL;
		    bp->b_bufobj = NULL;
	}
	/*
	 * release the physical I/O buffer
	 */
	if (bp->b_flags & B_ASYNC) {
		mtx_lock(&swbuf_mtx);
		if (++nsw_wcount_async == 1)
			wakeup(&nsw_wcount_async);
		mtx_unlock(&swbuf_mtx);
	}
	uma_zfree((bp->b_iocmd == BIO_READ) ? swrbuf_zone : swwbuf_zone, bp);
}