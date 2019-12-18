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
struct swdevt {int sw_flags; scalar_t__ sw_first; int sw_used; int /*<<< orphan*/  sw_blist; } ;
typedef  scalar_t__ daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLIST_MAX_ALLOC ; 
 scalar_t__ SWAPBLK_NONE ; 
 int SW_CLOSING ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct swdevt* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct swdevt* TAILQ_NEXT (struct swdevt*,int /*<<< orphan*/ ) ; 
 scalar_t__ blist_alloc (int /*<<< orphan*/ ,int*,int) ; 
 int imin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sw_dev_mtx ; 
 int /*<<< orphan*/  sw_list ; 
 int swap_pager_almost_full ; 
 int swap_pager_avail ; 
 int swap_pager_full ; 
 struct swdevt* swdevhd ; 
 int /*<<< orphan*/  swp_sizecheck () ; 
 int /*<<< orphan*/  swtailq ; 

__attribute__((used)) static daddr_t
swp_pager_getswapspace(int *io_npages, int limit)
{
	daddr_t blk;
	struct swdevt *sp;
	int mpages, npages;

	blk = SWAPBLK_NONE;
	mpages = *io_npages;
	npages = imin(BLIST_MAX_ALLOC, mpages);
	mtx_lock(&sw_dev_mtx);
	sp = swdevhd;
	while (!TAILQ_EMPTY(&swtailq)) {
		if (sp == NULL)
			sp = TAILQ_FIRST(&swtailq);
		if ((sp->sw_flags & SW_CLOSING) == 0)
			blk = blist_alloc(sp->sw_blist, &npages, mpages);
		if (blk != SWAPBLK_NONE)
			break;
		sp = TAILQ_NEXT(sp, sw_list);
		if (swdevhd == sp) {
			if (npages <= limit)
				break;
			mpages = npages - 1;
			npages >>= 1;
		}
	}
	if (blk != SWAPBLK_NONE) {
		*io_npages = npages;
		blk += sp->sw_first;
		sp->sw_used += npages;
		swap_pager_avail -= npages;
		swp_sizecheck();
		swdevhd = TAILQ_NEXT(sp, sw_list);
	} else {
		if (swap_pager_full != 2) {
			printf("swp_pager_getswapspace(%d): failed\n",
			    *io_npages);
			swap_pager_full = 2;
			swap_pager_almost_full = 1;
		}
		swdevhd = NULL;
	}
	mtx_unlock(&sw_dev_mtx);
	return (blk);
}