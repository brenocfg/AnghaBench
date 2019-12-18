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
struct bufqueue {int /*<<< orphan*/  bq_queue; } ;
struct bufdomain {int bd_wanted; struct bufqueue* bd_cleanq; } ;
struct buf {scalar_t__ b_kvasize; int b_flags; int b_vflags; scalar_t__ b_qindex; scalar_t__ b_domain; } ;

/* Variables and functions */
 scalar_t__ BD_DOMAIN (struct bufdomain*) ; 
 scalar_t__ BD_LOCKPTR (struct bufdomain*) ; 
 int /*<<< orphan*/  BQ_LOCK (struct bufqueue*) ; 
 scalar_t__ BQ_LOCKPTR (struct bufqueue*) ; 
 int /*<<< orphan*/  BQ_UNLOCK (struct bufqueue*) ; 
 scalar_t__ BUF_LOCK (struct buf*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUF_UNLOCK (struct buf*) ; 
 int BV_BKGRDERR ; 
 int BV_BKGRDINPROG ; 
 int B_INVAL ; 
 int B_REUSE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_NOWAIT ; 
 scalar_t__ QUEUE_CLEAN ; 
 struct buf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 struct buf* TAILQ_NEXT (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_freelist ; 
 int /*<<< orphan*/  bq_remove (struct bufqueue*,struct buf*) ; 
 int /*<<< orphan*/  bqrelse (struct buf*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  bufdefragcnt ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
buf_recycle(struct bufdomain *bd, bool kva)
{
	struct bufqueue *bq;
	struct buf *bp, *nbp;

	if (kva)
		counter_u64_add(bufdefragcnt, 1);
	nbp = NULL;
	bq = bd->bd_cleanq;
	BQ_LOCK(bq);
	KASSERT(BQ_LOCKPTR(bq) == BD_LOCKPTR(bd),
	    ("buf_recycle: Locks don't match"));
	nbp = TAILQ_FIRST(&bq->bq_queue);

	/*
	 * Run scan, possibly freeing data and/or kva mappings on the fly
	 * depending.
	 */
	while ((bp = nbp) != NULL) {
		/*
		 * Calculate next bp (we can only use it if we do not
		 * release the bqlock).
		 */
		nbp = TAILQ_NEXT(bp, b_freelist);

		/*
		 * If we are defragging then we need a buffer with 
		 * some kva to reclaim.
		 */
		if (kva && bp->b_kvasize == 0)
			continue;

		if (BUF_LOCK(bp, LK_EXCLUSIVE | LK_NOWAIT, NULL) != 0)
			continue;

		/*
		 * Implement a second chance algorithm for frequently
		 * accessed buffers.
		 */
		if ((bp->b_flags & B_REUSE) != 0) {
			TAILQ_REMOVE(&bq->bq_queue, bp, b_freelist);
			TAILQ_INSERT_TAIL(&bq->bq_queue, bp, b_freelist);
			bp->b_flags &= ~B_REUSE;
			BUF_UNLOCK(bp);
			continue;
		}

		/*
		 * Skip buffers with background writes in progress.
		 */
		if ((bp->b_vflags & BV_BKGRDINPROG) != 0) {
			BUF_UNLOCK(bp);
			continue;
		}

		KASSERT(bp->b_qindex == QUEUE_CLEAN,
		    ("buf_recycle: inconsistent queue %d bp %p",
		    bp->b_qindex, bp));
		KASSERT(bp->b_domain == BD_DOMAIN(bd),
		    ("getnewbuf: queue domain %d doesn't match request %d",
		    bp->b_domain, (int)BD_DOMAIN(bd)));
		/*
		 * NOTE:  nbp is now entirely invalid.  We can only restart
		 * the scan from this point on.
		 */
		bq_remove(bq, bp);
		BQ_UNLOCK(bq);

		/*
		 * Requeue the background write buffer with error and
		 * restart the scan.
		 */
		if ((bp->b_vflags & BV_BKGRDERR) != 0) {
			bqrelse(bp);
			BQ_LOCK(bq);
			nbp = TAILQ_FIRST(&bq->bq_queue);
			continue;
		}
		bp->b_flags |= B_INVAL;
		brelse(bp);
		return (0);
	}
	bd->bd_wanted = 1;
	BQ_UNLOCK(bq);

	return (ENOBUFS);
}