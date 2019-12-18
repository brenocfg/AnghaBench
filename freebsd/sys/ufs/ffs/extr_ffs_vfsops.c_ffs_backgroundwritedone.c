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
struct bufobj {int dummy; } ;
struct buf {int b_ioflags; int b_vflags; int /*<<< orphan*/  b_xflags; int /*<<< orphan*/  b_flags; int /*<<< orphan*/  b_dep; int /*<<< orphan*/  b_lblkno; struct bufobj* b_bufobj; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 int /*<<< orphan*/  BO_LOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_UNLOCK (struct bufobj*) ; 
 int BV_BKGRDERR ; 
 int BV_BKGRDINPROG ; 
 int BV_BKGRDWAIT ; 
 int /*<<< orphan*/  B_CACHE ; 
 int /*<<< orphan*/  B_INVAL ; 
 int /*<<< orphan*/  B_NOCACHE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_complete (struct buf*) ; 
 int /*<<< orphan*/  bufdone (struct buf*) ; 
 struct buf* gbincore (struct bufobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pbrelvp (struct buf*) ; 
 int /*<<< orphan*/  softdep_move_dependencies (struct buf*,struct buf*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ffs_backgroundwritedone(struct buf *bp)
{
	struct bufobj *bufobj;
	struct buf *origbp;

	/*
	 * Find the original buffer that we are writing.
	 */
	bufobj = bp->b_bufobj;
	BO_LOCK(bufobj);
	if ((origbp = gbincore(bp->b_bufobj, bp->b_lblkno)) == NULL)
		panic("backgroundwritedone: lost buffer");

	/*
	 * We should mark the cylinder group buffer origbp as
	 * dirty, to not loose the failed write.
	 */
	if ((bp->b_ioflags & BIO_ERROR) != 0)
		origbp->b_vflags |= BV_BKGRDERR;
	BO_UNLOCK(bufobj);
	/*
	 * Process dependencies then return any unfinished ones.
	 */
	if (!LIST_EMPTY(&bp->b_dep) && (bp->b_ioflags & BIO_ERROR) == 0)
		buf_complete(bp);
#ifdef SOFTUPDATES
	if (!LIST_EMPTY(&bp->b_dep))
		softdep_move_dependencies(bp, origbp);
#endif
	/*
	 * This buffer is marked B_NOCACHE so when it is released
	 * by biodone it will be tossed.
	 */
	bp->b_flags |= B_NOCACHE;
	bp->b_flags &= ~B_CACHE;
	pbrelvp(bp);

	/*
	 * Prevent brelse() from trying to keep and re-dirtying bp on
	 * errors. It causes b_bufobj dereference in
	 * bdirty()/reassignbuf(), and b_bufobj was cleared in
	 * pbrelvp() above.
	 */
	if ((bp->b_ioflags & BIO_ERROR) != 0)
		bp->b_flags |= B_INVAL;
	bufdone(bp);
	BO_LOCK(bufobj);
	/*
	 * Clear the BV_BKGRDINPROG flag in the original buffer
	 * and awaken it if it is waiting for the write to complete.
	 * If BV_BKGRDINPROG is not set in the original buffer it must
	 * have been released and re-instantiated - which is not legal.
	 */
	KASSERT((origbp->b_vflags & BV_BKGRDINPROG),
	    ("backgroundwritedone: lost buffer2"));
	origbp->b_vflags &= ~BV_BKGRDINPROG;
	if (origbp->b_vflags & BV_BKGRDWAIT) {
		origbp->b_vflags &= ~BV_BKGRDWAIT;
		wakeup(&origbp->b_xflags);
	}
	BO_UNLOCK(bufobj);
}