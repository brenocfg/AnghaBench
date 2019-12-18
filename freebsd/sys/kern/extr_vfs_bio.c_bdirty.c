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
struct buf {int b_flags; scalar_t__ b_qindex; int /*<<< orphan*/  b_iocmd; int /*<<< orphan*/ * b_bufobj; int /*<<< orphan*/  b_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_WRITE ; 
 int B_DELWRI ; 
 int B_RELBUF ; 
 int B_REMFREE ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_BUF ; 
 scalar_t__ QUEUE_NONE ; 
 int /*<<< orphan*/  bdirtyadd (struct buf*) ; 
 int /*<<< orphan*/  reassignbuf (struct buf*) ; 

void
bdirty(struct buf *bp)
{

	CTR3(KTR_BUF, "bdirty(%p) vp %p flags %X",
	    bp, bp->b_vp, bp->b_flags);
	KASSERT(bp->b_bufobj != NULL, ("No b_bufobj %p", bp));
	KASSERT(bp->b_flags & B_REMFREE || bp->b_qindex == QUEUE_NONE,
	    ("bdirty: buffer %p still on queue %d", bp, bp->b_qindex));
	bp->b_flags &= ~(B_RELBUF);
	bp->b_iocmd = BIO_WRITE;

	if ((bp->b_flags & B_DELWRI) == 0) {
		bp->b_flags |= /* XXX B_DONE | */ B_DELWRI;
		reassignbuf(bp);
		bdirtyadd(bp);
	}
}