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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int ;
struct netmap_ring {scalar_t__ head; scalar_t__ cur; scalar_t__ tail; } ;
struct netmap_kring {scalar_t__ nkr_num_slots; scalar_t__ const nr_hwcur; scalar_t__ const nr_hwtail; scalar_t__ rcur; scalar_t__ rhead; scalar_t__ rtail; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_FAIL_ON (int) ; 
 int /*<<< orphan*/  nm_prdis (int,char*,int /*<<< orphan*/ ,scalar_t__ const,scalar_t__ const,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nm_prlim (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

u_int
nm_rxsync_prologue(struct netmap_kring *kring, struct netmap_ring *ring)
{
	uint32_t const n = kring->nkr_num_slots;
	uint32_t head, cur;

	nm_prdis(5,"%s kc %d kt %d h %d c %d t %d",
		kring->name,
		kring->nr_hwcur, kring->nr_hwtail,
		ring->head, ring->cur, ring->tail);
	/*
	 * Before storing the new values, we should check they do not
	 * move backwards. However:
	 * - head is not an issue because the previous value is hwcur;
	 * - cur could in principle go back, however it does not matter
	 *   because we are processing a brand new rxsync()
	 */
	cur = kring->rcur = ring->cur;	/* read only once */
	head = kring->rhead = ring->head;	/* read only once */
#if 1 /* kernel sanity checks */
	NM_FAIL_ON(kring->nr_hwcur >= n || kring->nr_hwtail >= n);
#endif /* kernel sanity checks */
	/* user sanity checks */
	if (kring->nr_hwtail >= kring->nr_hwcur) {
		/* want hwcur <= rhead <= hwtail */
		NM_FAIL_ON(head < kring->nr_hwcur || head > kring->nr_hwtail);
		/* and also rhead <= rcur <= hwtail */
		NM_FAIL_ON(cur < head || cur > kring->nr_hwtail);
	} else {
		/* we need rhead outside hwtail..hwcur */
		NM_FAIL_ON(head < kring->nr_hwcur && head > kring->nr_hwtail);
		/* two cases now: head <= hwtail or head >= hwcur  */
		if (head <= kring->nr_hwtail) {
			/* want head <= cur <= hwtail */
			NM_FAIL_ON(cur < head || cur > kring->nr_hwtail);
		} else {
			/* cur must be outside hwtail..head */
			NM_FAIL_ON(cur < head && cur > kring->nr_hwtail);
		}
	}
	if (ring->tail != kring->rtail) {
		nm_prlim(5, "%s tail overwritten was %d need %d",
			kring->name,
			ring->tail, kring->rtail);
		ring->tail = kring->rtail;
	}
	return head;
}