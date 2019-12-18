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
struct mtx {int dummy; } ;
struct buf {int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_DONE ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct buf*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 
 int /*<<< orphan*/  wakeup (struct buf*) ; 

void
bdone(struct buf *bp)
{
	struct mtx *mtxp;

	mtxp = mtx_pool_find(mtxpool_sleep, bp);
	mtx_lock(mtxp);
	bp->b_flags |= B_DONE;
	wakeup(bp);
	mtx_unlock(mtxp);
}