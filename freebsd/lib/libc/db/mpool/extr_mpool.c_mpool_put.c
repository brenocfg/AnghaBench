#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_5__ {int flags; int pgno; } ;
struct TYPE_4__ {int /*<<< orphan*/  pageput; } ;
typedef  TYPE_1__ MPOOL ;
typedef  TYPE_2__ BKT ;

/* Variables and functions */
 int MPOOL_DIRTY ; 
 int MPOOL_PINNED ; 
 int RET_SUCCESS ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int
mpool_put(MPOOL *mp, void *page, u_int flags)
{
	BKT *bp;

#ifdef STATISTICS
	++mp->pageput;
#endif
	bp = (BKT *)((char *)page - sizeof(BKT));
#ifdef DEBUG
	if (!(bp->flags & MPOOL_PINNED)) {
		(void)fprintf(stderr,
		    "mpool_put: page %d not pinned\n", bp->pgno);
		abort();
	}
#endif
	bp->flags &= ~MPOOL_PINNED;
	if (flags & MPOOL_DIRTY)
		bp->flags |= flags & MPOOL_DIRTY;
	return (RET_SUCCESS);
}