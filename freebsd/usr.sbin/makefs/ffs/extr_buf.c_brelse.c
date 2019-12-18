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
struct buf {scalar_t__ b_lblkno; struct buf* b_data; scalar_t__ b_bcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_tailq ; 
 int /*<<< orphan*/  buftail ; 
 int /*<<< orphan*/  free (struct buf*) ; 

void
brelse(struct buf *bp)
{

	assert (bp != NULL);
	assert (bp->b_data != NULL);

	if (bp->b_lblkno < 0) {
		/*
		 * XXX	don't remove any buffers with negative logical block
		 *	numbers (lblkno), so that we retain the mapping
		 *	of negative lblkno -> real blkno that ffs_balloc()
		 *	sets up.
		 *
		 *	if we instead released these buffers, and implemented
		 *	ufs_strategy() (and ufs_bmaparray()) and called those
		 *	from bread() and bwrite() to convert the lblkno to
		 *	a real blkno, we'd add a lot more code & complexity
		 *	and reading off disk, for little gain, because this
		 *	simple hack works for our purpose.
		 */
		bp->b_bcount = 0;
		return;
	}

	TAILQ_REMOVE(&buftail, bp, b_tailq);
	free(bp->b_data);
	free(bp);
}