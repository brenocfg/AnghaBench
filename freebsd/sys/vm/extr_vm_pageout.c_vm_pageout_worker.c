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
typedef  scalar_t__ u_int ;
struct vm_domain {scalar_t__ vmd_segs; scalar_t__ vmd_free_count; int /*<<< orphan*/  vmd_pid; int /*<<< orphan*/  vmd_pageout_wanted; int /*<<< orphan*/  vmd_last_active_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PDROP ; 
 int PVM ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_CNT_INC (int /*<<< orphan*/ ) ; 
 struct vm_domain* VM_DOMAIN (int) ; 
 int VM_INACT_SCAN_RATE ; 
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,int) ; 
 int hz ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 scalar_t__ mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int pidctrl_daemon (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ticks ; 
 int /*<<< orphan*/  v_pdwakeups ; 
 int /*<<< orphan*/  vm_domain_pageout_lock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_pageout_lockptr (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_pageout_unlock (struct vm_domain*) ; 
 int vm_pageout_active_target (struct vm_domain*) ; 
 scalar_t__ vm_pageout_lowmem () ; 
 int /*<<< orphan*/  vm_pageout_scan_active (struct vm_domain*,int) ; 
 int vm_pageout_scan_inactive (struct vm_domain*,int,int*) ; 
 scalar_t__ vm_paging_needed (struct vm_domain*,scalar_t__) ; 

__attribute__((used)) static void
vm_pageout_worker(void *arg)
{
	struct vm_domain *vmd;
	u_int ofree;
	int addl_shortage, domain, shortage;
	bool target_met;

	domain = (uintptr_t)arg;
	vmd = VM_DOMAIN(domain);
	shortage = 0;
	target_met = true;

	/*
	 * XXXKIB It could be useful to bind pageout daemon threads to
	 * the cores belonging to the domain, from which vm_page_array
	 * is allocated.
	 */

	KASSERT(vmd->vmd_segs != 0, ("domain without segments"));
	vmd->vmd_last_active_scan = ticks;

	/*
	 * The pageout daemon worker is never done, so loop forever.
	 */
	while (TRUE) {
		vm_domain_pageout_lock(vmd);

		/*
		 * We need to clear wanted before we check the limits.  This
		 * prevents races with wakers who will check wanted after they
		 * reach the limit.
		 */
		atomic_store_int(&vmd->vmd_pageout_wanted, 0);

		/*
		 * Might the page daemon need to run again?
		 */
		if (vm_paging_needed(vmd, vmd->vmd_free_count)) {
			/*
			 * Yes.  If the scan failed to produce enough free
			 * pages, sleep uninterruptibly for some time in the
			 * hope that the laundry thread will clean some pages.
			 */
			vm_domain_pageout_unlock(vmd);
			if (!target_met)
				pause("pwait", hz / VM_INACT_SCAN_RATE);
		} else {
			/*
			 * No, sleep until the next wakeup or until pages
			 * need to have their reference stats updated.
			 */
			if (mtx_sleep(&vmd->vmd_pageout_wanted,
			    vm_domain_pageout_lockptr(vmd), PDROP | PVM,
			    "psleep", hz / VM_INACT_SCAN_RATE) == 0)
				VM_CNT_INC(v_pdwakeups);
		}

		/* Prevent spurious wakeups by ensuring that wanted is set. */
		atomic_store_int(&vmd->vmd_pageout_wanted, 1);

		/*
		 * Use the controller to calculate how many pages to free in
		 * this interval, and scan the inactive queue.  If the lowmem
		 * handlers appear to have freed up some pages, subtract the
		 * difference from the inactive queue scan target.
		 */
		shortage = pidctrl_daemon(&vmd->vmd_pid, vmd->vmd_free_count);
		if (shortage > 0) {
			ofree = vmd->vmd_free_count;
			if (vm_pageout_lowmem() && vmd->vmd_free_count > ofree)
				shortage -= min(vmd->vmd_free_count - ofree,
				    (u_int)shortage);
			target_met = vm_pageout_scan_inactive(vmd, shortage,
			    &addl_shortage);
		} else
			addl_shortage = 0;

		/*
		 * Scan the active queue.  A positive value for shortage
		 * indicates that we must aggressively deactivate pages to avoid
		 * a shortfall.
		 */
		shortage = vm_pageout_active_target(vmd) + addl_shortage;
		vm_pageout_scan_active(vmd, shortage);
	}
}