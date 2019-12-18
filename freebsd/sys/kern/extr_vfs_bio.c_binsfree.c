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
struct bufqueue {int dummy; } ;
struct bufdomain {scalar_t__ bd_lim; struct bufqueue bd_dirtyq; struct bufqueue* bd_cleanq; struct bufqueue* bd_subq; } ;
struct buf {int b_flags; int b_qindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ_UNLOCK (struct bufqueue*) ; 
 int /*<<< orphan*/  BUF_ASSERT_XLOCKED (struct buf*) ; 
 int /*<<< orphan*/  BUF_UNLOCK (struct buf*) ; 
 int B_REMFREE ; 
 int B_REUSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int QUEUE_CLEAN ; 
 int QUEUE_DIRTY ; 
 int /*<<< orphan*/  bq_insert (struct bufqueue*,struct buf*,int) ; 
 int /*<<< orphan*/  bq_remove (struct bufqueue*,struct buf*) ; 
 struct bufdomain* bufdomain (struct buf*) ; 
 struct bufqueue* bufqueue_acquire (struct buf*) ; 
 int /*<<< orphan*/  cpuid ; 

__attribute__((used)) static void
binsfree(struct buf *bp, int qindex)
{
	struct bufdomain *bd;
	struct bufqueue *bq;

	KASSERT(qindex == QUEUE_CLEAN || qindex == QUEUE_DIRTY,
	    ("binsfree: Invalid qindex %d", qindex));
	BUF_ASSERT_XLOCKED(bp);

	/*
	 * Handle delayed bremfree() processing.
	 */
	if (bp->b_flags & B_REMFREE) {
		if (bp->b_qindex == qindex) {
			bp->b_flags |= B_REUSE;
			bp->b_flags &= ~B_REMFREE;
			BUF_UNLOCK(bp);
			return;
		}
		bq = bufqueue_acquire(bp);
		bq_remove(bq, bp);
		BQ_UNLOCK(bq);
	}
	bd = bufdomain(bp);
	if (qindex == QUEUE_CLEAN) {
		if (bd->bd_lim != 0)
			bq = &bd->bd_subq[PCPU_GET(cpuid)];
		else
			bq = bd->bd_cleanq;
	} else
		bq = &bd->bd_dirtyq;
	bq_insert(bq, bp, true);
}