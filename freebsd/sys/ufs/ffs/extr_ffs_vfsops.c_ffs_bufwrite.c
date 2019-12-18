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
struct cg {int /*<<< orphan*/  cg_time; int /*<<< orphan*/  cg_old_time; int /*<<< orphan*/  cg_ckhash; } ;
struct buf {int b_flags; int b_vflags; int b_xflags; scalar_t__ b_data; int /*<<< orphan*/  b_bcount; int /*<<< orphan*/  b_dep; int /*<<< orphan*/  b_vp; int /*<<< orphan*/ * b_iodone; int /*<<< orphan*/  b_offset; int /*<<< orphan*/  b_blkno; int /*<<< orphan*/  b_lblkno; int /*<<< orphan*/  b_bufobj; int /*<<< orphan*/  b_bufsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BO_LOCKPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BO_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUF_ISLOCKED (struct buf*) ; 
 int BV_BKGRDERR ; 
 int BV_BKGRDINPROG ; 
 int BV_BKGRDWAIT ; 
 int BX_BKGRDMARKER ; 
 int BX_BKGRDWRITE ; 
 int BX_CYLGRP ; 
 int BX_FSPRIV ; 
 int B_ASYNC ; 
 int B_INVAL ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GB_NOWAIT_BD ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KTR_BUF ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int /*<<< orphan*/  bqrelse (struct buf*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  buf_dirty_count_severe () ; 
 int /*<<< orphan*/  buf_mapped (struct buf*) ; 
 int bufwrite (struct buf*) ; 
 int /*<<< orphan*/  bundirty (struct buf*) ; 
 int /*<<< orphan*/  calculate_crc32c (long,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dobkgrdwrite ; 
 int /*<<< orphan*/ * ffs_backgroundwritedone ; 
 struct buf* geteblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pbgetvp (int /*<<< orphan*/ ,struct buf*) ; 
 scalar_t__ softdep_move_dependencies (struct buf*,struct buf*) ; 
 int /*<<< orphan*/  time_second ; 
 int /*<<< orphan*/  vm_page_count_severe () ; 

__attribute__((used)) static int
ffs_bufwrite(struct buf *bp)
{
	struct buf *newbp;
	struct cg *cgp;

	CTR3(KTR_BUF, "bufwrite(%p) vp %p flags %X", bp, bp->b_vp, bp->b_flags);
	if (bp->b_flags & B_INVAL) {
		brelse(bp);
		return (0);
	}

	if (!BUF_ISLOCKED(bp))
		panic("bufwrite: buffer is not busy???");
	/*
	 * If a background write is already in progress, delay
	 * writing this block if it is asynchronous. Otherwise
	 * wait for the background write to complete.
	 */
	BO_LOCK(bp->b_bufobj);
	if (bp->b_vflags & BV_BKGRDINPROG) {
		if (bp->b_flags & B_ASYNC) {
			BO_UNLOCK(bp->b_bufobj);
			bdwrite(bp);
			return (0);
		}
		bp->b_vflags |= BV_BKGRDWAIT;
		msleep(&bp->b_xflags, BO_LOCKPTR(bp->b_bufobj), PRIBIO,
		    "bwrbg", 0);
		if (bp->b_vflags & BV_BKGRDINPROG)
			panic("bufwrite: still writing");
	}
	bp->b_vflags &= ~BV_BKGRDERR;
	BO_UNLOCK(bp->b_bufobj);

	/*
	 * If this buffer is marked for background writing and we
	 * do not have to wait for it, make a copy and write the
	 * copy so as to leave this buffer ready for further use.
	 *
	 * This optimization eats a lot of memory.  If we have a page
	 * or buffer shortfall we can't do it.
	 */
	if (dobkgrdwrite && (bp->b_xflags & BX_BKGRDWRITE) &&
	    (bp->b_flags & B_ASYNC) &&
	    !vm_page_count_severe() &&
	    !buf_dirty_count_severe()) {
		KASSERT(bp->b_iodone == NULL,
		    ("bufwrite: needs chained iodone (%p)", bp->b_iodone));

		/* get a new block */
		newbp = geteblk(bp->b_bufsize, GB_NOWAIT_BD);
		if (newbp == NULL)
			goto normal_write;

		KASSERT(buf_mapped(bp), ("Unmapped cg"));
		memcpy(newbp->b_data, bp->b_data, bp->b_bufsize);
		BO_LOCK(bp->b_bufobj);
		bp->b_vflags |= BV_BKGRDINPROG;
		BO_UNLOCK(bp->b_bufobj);
		newbp->b_xflags |=
		    (bp->b_xflags & BX_FSPRIV) | BX_BKGRDMARKER;
		newbp->b_lblkno = bp->b_lblkno;
		newbp->b_blkno = bp->b_blkno;
		newbp->b_offset = bp->b_offset;
		newbp->b_iodone = ffs_backgroundwritedone;
		newbp->b_flags |= B_ASYNC;
		newbp->b_flags &= ~B_INVAL;
		pbgetvp(bp->b_vp, newbp);

#ifdef SOFTUPDATES
		/*
		 * Move over the dependencies.  If there are rollbacks,
		 * leave the parent buffer dirtied as it will need to
		 * be written again.
		 */
		if (LIST_EMPTY(&bp->b_dep) ||
		    softdep_move_dependencies(bp, newbp) == 0)
			bundirty(bp);
#else
		bundirty(bp);
#endif

		/*
		 * Initiate write on the copy, release the original.  The
		 * BKGRDINPROG flag prevents it from going away until 
		 * the background write completes. We have to recalculate
		 * its check hash in case the buffer gets freed and then
		 * reconstituted from the buffer cache during a later read.
		 */
		if ((bp->b_xflags & BX_CYLGRP) != 0) {
			cgp = (struct cg *)bp->b_data;
			cgp->cg_ckhash = 0;
			cgp->cg_ckhash =
			    calculate_crc32c(~0L, bp->b_data, bp->b_bcount);
		}
		bqrelse(bp);
		bp = newbp;
	} else
		/* Mark the buffer clean */
		bundirty(bp);


	/* Let the normal bufwrite do the rest for us */
normal_write:
	/*
	 * If we are writing a cylinder group, update its time.
	 */
	if ((bp->b_xflags & BX_CYLGRP) != 0) {
		cgp = (struct cg *)bp->b_data;
		cgp->cg_old_time = cgp->cg_time = time_second;
	}
	return (bufwrite(bp));
}