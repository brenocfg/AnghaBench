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
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ_LOCK (struct bufqueue*) ; 
 int /*<<< orphan*/  BQ_UNLOCK (struct bufqueue*) ; 
 struct bufqueue* bufqueue (struct buf*) ; 

__attribute__((used)) static struct bufqueue *
bufqueue_acquire(struct buf *bp)
{
	struct bufqueue *bq, *nbq;

	/*
	 * bp can be pushed from a per-cpu queue to the
	 * cleanq while we're waiting on the lock.  Retry
	 * if the queues don't match.
	 */
	bq = bufqueue(bp);
	BQ_LOCK(bq);
	for (;;) {
		nbq = bufqueue(bp);
		if (bq == nbq)
			break;
		BQ_UNLOCK(bq);
		BQ_LOCK(nbq);
		bq = nbq;
	}
	return (bq);
}