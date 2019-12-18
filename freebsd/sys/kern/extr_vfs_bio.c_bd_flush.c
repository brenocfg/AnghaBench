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
struct bufqueue {scalar_t__ bq_len; int /*<<< orphan*/  bq_subqueue; int /*<<< orphan*/  bq_queue; } ;
struct bufdomain {struct bufqueue* bd_cleanq; scalar_t__ bd_wanted; } ;
struct buf {int /*<<< orphan*/  b_subqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_LOCK (struct bufdomain*) ; 
 int /*<<< orphan*/  BD_UNLOCK (struct bufdomain*) ; 
 int /*<<< orphan*/  BQ_ASSERT_LOCKED (struct bufqueue*) ; 
 struct buf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_freelist ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
bd_flush(struct bufdomain *bd, struct bufqueue *bq)
{
	struct buf *bp;

	BQ_ASSERT_LOCKED(bq);
	if (bq != bd->bd_cleanq) {
		BD_LOCK(bd);
		while ((bp = TAILQ_FIRST(&bq->bq_queue)) != NULL) {
			TAILQ_REMOVE(&bq->bq_queue, bp, b_freelist);
			TAILQ_INSERT_TAIL(&bd->bd_cleanq->bq_queue, bp,
			    b_freelist);
			bp->b_subqueue = bd->bd_cleanq->bq_subqueue;
		}
		bd->bd_cleanq->bq_len += bq->bq_len;
		bq->bq_len = 0;
	}
	if (bd->bd_wanted) {
		bd->bd_wanted = 0;
		wakeup(&bd->bd_wanted);
	}
	if (bq != bd->bd_cleanq)
		BD_UNLOCK(bd);
}