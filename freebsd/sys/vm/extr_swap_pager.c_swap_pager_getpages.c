#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct buf {int b_bcount; int b_bufsize; int b_npages; int b_pgbefore; int b_pgafter; scalar_t__ b_blkno; int /*<<< orphan*/  b_bufobj; void* b_wcred; void* b_rcred; int /*<<< orphan*/  b_iodone; int /*<<< orphan*/  b_iocmd; int /*<<< orphan*/  b_flags; TYPE_1__** b_pages; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_20__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_19__ {int /*<<< orphan*/  handle; } ;
struct TYPE_18__ {int pindex; int oflags; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  BUF_KERNPROC (struct buf*) ; 
 int /*<<< orphan*/  B_PAGING ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PSWP ; 
 scalar_t__ SWAPBLK_NONE ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_PREV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_ALLOC_NORMAL ; 
 int /*<<< orphan*/  VM_CNT_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_OBJECT_SLEEP (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 int VM_PAGER_ERROR ; 
 int VM_PAGER_FAIL ; 
 int VM_PAGER_OK ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 int VPO_SWAPINPROG ; 
 int VPO_SWAPSLEEP ; 
 void* crhold (int /*<<< orphan*/ ) ; 
 int hz ; 
 int imin (int,int) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  pglist ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap_pager_haspage (TYPE_2__*,int,int*,int*) ; 
 int /*<<< orphan*/  swp_pager_async_iodone ; 
 scalar_t__ swp_pager_meta_ctl (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_pager_strategy (struct buf*) ; 
 int /*<<< orphan*/  swrbuf_zone ; 
 TYPE_6__ thread0 ; 
 struct buf* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_intrans ; 
 int /*<<< orphan*/  v_swapin ; 
 int /*<<< orphan*/  v_swappgsin ; 
 int /*<<< orphan*/  vm_object_pip_add (TYPE_2__*,int) ; 
 TYPE_1__* vm_page_alloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
swap_pager_getpages(vm_object_t object, vm_page_t *ma, int count, int *rbehind,
    int *rahead)
{
	struct buf *bp;
	vm_page_t bm, mpred, msucc, p;
	vm_pindex_t pindex;
	daddr_t blk;
	int i, maxahead, maxbehind, reqcount;

	reqcount = count;

	/*
	 * Determine the final number of read-behind pages and
	 * allocate them BEFORE releasing the object lock.  Otherwise,
	 * there can be a problematic race with vm_object_split().
	 * Specifically, vm_object_split() might first transfer pages
	 * that precede ma[0] in the current object to a new object,
	 * and then this function incorrectly recreates those pages as
	 * read-behind pages in the current object.
	 */
	if (!swap_pager_haspage(object, ma[0]->pindex, &maxbehind, &maxahead))
		return (VM_PAGER_FAIL);

	/*
	 * Clip the readahead and readbehind ranges to exclude resident pages.
	 */
	if (rahead != NULL) {
		KASSERT(reqcount - 1 <= maxahead,
		    ("page count %d extends beyond swap block", reqcount));
		*rahead = imin(*rahead, maxahead - (reqcount - 1));
		pindex = ma[reqcount - 1]->pindex;
		msucc = TAILQ_NEXT(ma[reqcount - 1], listq);
		if (msucc != NULL && msucc->pindex - pindex - 1 < *rahead)
			*rahead = msucc->pindex - pindex - 1;
	}
	if (rbehind != NULL) {
		*rbehind = imin(*rbehind, maxbehind);
		pindex = ma[0]->pindex;
		mpred = TAILQ_PREV(ma[0], pglist, listq);
		if (mpred != NULL && pindex - mpred->pindex - 1 < *rbehind)
			*rbehind = pindex - mpred->pindex - 1;
	}

	bm = ma[0];
	for (i = 0; i < count; i++)
		ma[i]->oflags |= VPO_SWAPINPROG;

	/*
	 * Allocate readahead and readbehind pages.
	 */
	if (rbehind != NULL) {
		for (i = 1; i <= *rbehind; i++) {
			p = vm_page_alloc(object, ma[0]->pindex - i,
			    VM_ALLOC_NORMAL);
			if (p == NULL)
				break;
			p->oflags |= VPO_SWAPINPROG;
			bm = p;
		}
		*rbehind = i - 1;
	}
	if (rahead != NULL) {
		for (i = 0; i < *rahead; i++) {
			p = vm_page_alloc(object,
			    ma[reqcount - 1]->pindex + i + 1, VM_ALLOC_NORMAL);
			if (p == NULL)
				break;
			p->oflags |= VPO_SWAPINPROG;
		}
		*rahead = i;
	}
	if (rbehind != NULL)
		count += *rbehind;
	if (rahead != NULL)
		count += *rahead;

	vm_object_pip_add(object, count);

	pindex = bm->pindex;
	blk = swp_pager_meta_ctl(object, pindex, 0);
	KASSERT(blk != SWAPBLK_NONE,
	    ("no swap blocking containing %p(%jx)", object, (uintmax_t)pindex));

	VM_OBJECT_WUNLOCK(object);
	bp = uma_zalloc(swrbuf_zone, M_WAITOK);
	/* Pages cannot leave the object while busy. */
	for (i = 0, p = bm; i < count; i++, p = TAILQ_NEXT(p, listq)) {
		MPASS(p->pindex == bm->pindex + i);
		bp->b_pages[i] = p;
	}

	bp->b_flags |= B_PAGING;
	bp->b_iocmd = BIO_READ;
	bp->b_iodone = swp_pager_async_iodone;
	bp->b_rcred = crhold(thread0.td_ucred);
	bp->b_wcred = crhold(thread0.td_ucred);
	bp->b_blkno = blk;
	bp->b_bcount = PAGE_SIZE * count;
	bp->b_bufsize = PAGE_SIZE * count;
	bp->b_npages = count;
	bp->b_pgbefore = rbehind != NULL ? *rbehind : 0;
	bp->b_pgafter = rahead != NULL ? *rahead : 0;

	VM_CNT_INC(v_swapin);
	VM_CNT_ADD(v_swappgsin, count);

	/*
	 * perform the I/O.  NOTE!!!  bp cannot be considered valid after
	 * this point because we automatically release it on completion.
	 * Instead, we look at the one page we are interested in which we
	 * still hold a lock on even through the I/O completion.
	 *
	 * The other pages in our ma[] array are also released on completion,
	 * so we cannot assume they are valid anymore either.
	 *
	 * NOTE: b_blkno is destroyed by the call to swapdev_strategy
	 */
	BUF_KERNPROC(bp);
	swp_pager_strategy(bp);

	/*
	 * Wait for the pages we want to complete.  VPO_SWAPINPROG is always
	 * cleared on completion.  If an I/O error occurs, SWAPBLK_NONE
	 * is set in the metadata for each page in the request.
	 */
	VM_OBJECT_WLOCK(object);
	while ((ma[0]->oflags & VPO_SWAPINPROG) != 0) {
		ma[0]->oflags |= VPO_SWAPSLEEP;
		VM_CNT_INC(v_intrans);
		if (VM_OBJECT_SLEEP(object, &object->handle, PSWP,
		    "swread", hz * 20)) {
			printf(
"swap_pager: indefinite wait buffer: bufobj: %p, blkno: %jd, size: %ld\n",
			    bp->b_bufobj, (intmax_t)bp->b_blkno, bp->b_bcount);
		}
	}

	/*
	 * If we had an unrecoverable read error pages will not be valid.
	 */
	for (i = 0; i < reqcount; i++)
		if (ma[i]->valid != VM_PAGE_BITS_ALL)
			return (VM_PAGER_ERROR);

	return (VM_PAGER_OK);

	/*
	 * A final note: in a low swap situation, we cannot deallocate swap
	 * and mark a page dirty here because the caller is likely to mark
	 * the page clean when we return, causing the page to possibly revert
	 * to all-zero's later.
	 */
}