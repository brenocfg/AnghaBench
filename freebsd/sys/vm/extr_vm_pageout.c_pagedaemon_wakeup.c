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
struct vm_domain {int /*<<< orphan*/  vmd_pageout_wanted; } ;

/* Variables and functions */
 struct vm_domain* VM_DOMAIN (int) ; 
 scalar_t__ atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ curproc ; 
 scalar_t__ pageproc ; 
 int /*<<< orphan*/  vm_domain_pageout_assert_unlocked (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_pageout_lock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_pageout_unlock (struct vm_domain*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
pagedaemon_wakeup(int domain)
{
	struct vm_domain *vmd;

	vmd = VM_DOMAIN(domain);
	vm_domain_pageout_assert_unlocked(vmd);
	if (curproc == pageproc)
		return;

	if (atomic_fetchadd_int(&vmd->vmd_pageout_wanted, 1) == 0) {
		vm_domain_pageout_lock(vmd);
		atomic_store_int(&vmd->vmd_pageout_wanted, 1);
		wakeup(&vmd->vmd_pageout_wanted);
		vm_domain_pageout_unlock(vmd);
	}
}