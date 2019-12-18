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
typedef  scalar_t__ u_long ;
struct ucred {int dummy; } ;
struct swdevt {scalar_t__ sw_nblks; int /*<<< orphan*/  sw_blist; int /*<<< orphan*/ * sw_id; int /*<<< orphan*/  (* sw_close ) (int /*<<< orphan*/ ,struct swdevt*) ;int /*<<< orphan*/  sw_flags; int /*<<< orphan*/  sw_vp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  M_VMPGDATA ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  SW_CLOSING ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct swdevt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blist_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ blist_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free (struct swdevt*,int /*<<< orphan*/ ) ; 
 int mac_system_check_swapoff (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nswap_lowat ; 
 scalar_t__ nswapdev ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct swdevt*) ; 
 int /*<<< orphan*/  sw_dev_mtx ; 
 int /*<<< orphan*/  sw_list ; 
 int swap_pager_almost_full ; 
 scalar_t__ swap_pager_avail ; 
 int swap_pager_full ; 
 int /*<<< orphan*/  swap_pager_swapoff (struct swdevt*) ; 
 int /*<<< orphan*/  swap_total ; 
 int /*<<< orphan*/  swdev_syscall_lock ; 
 struct swdevt* swdevhd ; 
 int /*<<< orphan*/  swtailq ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_free_count () ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
swapoff_one(struct swdevt *sp, struct ucred *cred)
{
	u_long nblks;
#ifdef MAC
	int error;
#endif

	sx_assert(&swdev_syscall_lock, SA_XLOCKED);
#ifdef MAC
	(void) vn_lock(sp->sw_vp, LK_EXCLUSIVE | LK_RETRY);
	error = mac_system_check_swapoff(cred, sp->sw_vp);
	(void) VOP_UNLOCK(sp->sw_vp, 0);
	if (error != 0)
		return (error);
#endif
	nblks = sp->sw_nblks;

	/*
	 * We can turn off this swap device safely only if the
	 * available virtual memory in the system will fit the amount
	 * of data we will have to page back in, plus an epsilon so
	 * the system doesn't become critically low on swap space.
	 */
	if (vm_free_count() + swap_pager_avail < nblks + nswap_lowat)
		return (ENOMEM);

	/*
	 * Prevent further allocations on this device.
	 */
	mtx_lock(&sw_dev_mtx);
	sp->sw_flags |= SW_CLOSING;
	swap_pager_avail -= blist_fill(sp->sw_blist, 0, nblks);
	swap_total -= nblks;
	mtx_unlock(&sw_dev_mtx);

	/*
	 * Page in the contents of the device and close it.
	 */
	swap_pager_swapoff(sp);

	sp->sw_close(curthread, sp);
	mtx_lock(&sw_dev_mtx);
	sp->sw_id = NULL;
	TAILQ_REMOVE(&swtailq, sp, sw_list);
	nswapdev--;
	if (nswapdev == 0) {
		swap_pager_full = 2;
		swap_pager_almost_full = 1;
	}
	if (swdevhd == sp)
		swdevhd = NULL;
	mtx_unlock(&sw_dev_mtx);
	blist_destroy(sp->sw_blist);
	free(sp, M_VMPGDATA);
	return (0);
}