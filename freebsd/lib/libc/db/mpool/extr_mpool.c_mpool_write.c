#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int off_t ;
struct TYPE_6__ {int pgno; int /*<<< orphan*/  flags; int /*<<< orphan*/  page; } ;
struct TYPE_5__ {int pagesize; int /*<<< orphan*/  pgcookie; int /*<<< orphan*/  (* pgin ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fd; int /*<<< orphan*/  (* pgout ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pagewrite; } ;
typedef  TYPE_1__ MPOOL ;
typedef  TYPE_2__ BKT ;

/* Variables and functions */
 int /*<<< orphan*/  MPOOL_DIRTY ; 
 int RET_ERROR ; 
 int RET_SUCCESS ; 
 scalar_t__ pwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpool_write(MPOOL *mp, BKT *bp)
{
	off_t off;

#ifdef STATISTICS
	++mp->pagewrite;
#endif

	/* Run through the user's filter. */
	if (mp->pgout)
		(mp->pgout)(mp->pgcookie, bp->pgno, bp->page);

	off = mp->pagesize * bp->pgno;
	if (pwrite(mp->fd, bp->page, mp->pagesize, off) != (ssize_t)mp->pagesize)
		return (RET_ERROR);

	/*
	 * Re-run through the input filter since this page may soon be
	 * accessed via the cache, and whatever the user's output filter
	 * did may screw things up if we don't let the input filter
	 * restore the in-core copy.
	 */
	if (mp->pgin)
		(mp->pgin)(mp->pgcookie, bp->pgno, bp->page);

	bp->flags &= ~MPOOL_DIRTY;
	return (RET_SUCCESS);
}