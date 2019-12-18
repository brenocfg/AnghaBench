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
typedef  int /*<<< orphan*/  u_char ;
struct mtx {int dummy; } ;
struct buf {int b_flags; } ;

/* Variables and functions */
 int B_DONE ; 
 int /*<<< orphan*/  msleep (struct buf*,struct mtx*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct buf*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 

void
bwait(struct buf *bp, u_char pri, const char *wchan)
{
	struct mtx *mtxp;

	mtxp = mtx_pool_find(mtxpool_sleep, bp);
	mtx_lock(mtxp);
	while ((bp->b_flags & B_DONE) == 0)
		msleep(bp, mtxp, pri, wchan, 0);
	mtx_unlock(mtxp);
}