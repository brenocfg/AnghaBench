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
struct bufqueue {scalar_t__ bq_index; scalar_t__ bq_len; int /*<<< orphan*/  bq_subqueue; int /*<<< orphan*/  bq_queue; } ;
struct bufdomain {scalar_t__ bd_lim; struct bufqueue* bd_cleanq; scalar_t__ bd_wanted; } ;
struct buf {scalar_t__ b_qindex; int b_flags; int /*<<< orphan*/  b_subqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ_LOCK (struct bufqueue*) ; 
 int /*<<< orphan*/  BQ_UNLOCK (struct bufqueue*) ; 
 int /*<<< orphan*/  BUF_UNLOCK (struct buf*) ; 
 int B_AGE ; 
 int B_REUSE ; 
 scalar_t__ QUEUE_CLEAN ; 
 scalar_t__ QUEUE_NONE ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_freelist ; 
 int /*<<< orphan*/  bd_flush (struct bufdomain*,struct bufqueue*) ; 
 struct bufdomain* bufdomain (struct buf*) ; 
 int /*<<< orphan*/  panic (char*,struct buf*) ; 

__attribute__((used)) static void
bq_insert(struct bufqueue *bq, struct buf *bp, bool unlock)
{
	struct bufdomain *bd;

	if (bp->b_qindex != QUEUE_NONE)
		panic("bq_insert: free buffer %p onto another queue?", bp);

	bd = bufdomain(bp);
	if (bp->b_flags & B_AGE) {
		/* Place this buf directly on the real queue. */
		if (bq->bq_index == QUEUE_CLEAN)
			bq = bd->bd_cleanq;
		BQ_LOCK(bq);
		TAILQ_INSERT_HEAD(&bq->bq_queue, bp, b_freelist);
	} else {
		BQ_LOCK(bq);
		TAILQ_INSERT_TAIL(&bq->bq_queue, bp, b_freelist);
	}
	bp->b_flags &= ~(B_AGE | B_REUSE);
	bq->bq_len++;
	bp->b_qindex = bq->bq_index;
	bp->b_subqueue = bq->bq_subqueue;

	/*
	 * Unlock before we notify so that we don't wakeup a waiter that
	 * fails a trylock on the buf and sleeps again.
	 */
	if (unlock)
		BUF_UNLOCK(bp);

	if (bp->b_qindex == QUEUE_CLEAN) {
		/*
		 * Flush the per-cpu queue and notify any waiters.
		 */
		if (bd->bd_wanted || (bq != bd->bd_cleanq &&
		    bq->bq_len >= bd->bd_lim))
			bd_flush(bd, bq);
	}
	BQ_UNLOCK(bq);
}