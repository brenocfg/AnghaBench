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
struct bufqueue {int /*<<< orphan*/  bq_index; int /*<<< orphan*/  bq_len; int /*<<< orphan*/  bq_queue; } ;
struct buf {int b_flags; int /*<<< orphan*/  b_qindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ_LOCK (struct bufqueue*) ; 
 int /*<<< orphan*/  BQ_UNLOCK (struct bufqueue*) ; 
 int B_AGE ; 
 int B_REUSE ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_freelist ; 
 struct bufqueue bqempty ; 

__attribute__((used)) static void
buf_release(void *arg, void **store, int cnt)
{
	struct bufqueue *bq;
	struct buf *bp;
        int i;

	bq = &bqempty;
	BQ_LOCK(bq);
        for (i = 0; i < cnt; i++) {
		bp = store[i];
		/* Inline bq_insert() to batch locking. */
		TAILQ_INSERT_TAIL(&bq->bq_queue, bp, b_freelist);
		bp->b_flags &= ~(B_AGE | B_REUSE);
		bq->bq_len++;
		bp->b_qindex = bq->bq_index;
	}
	BQ_UNLOCK(bq);
}