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
struct vm_domain {scalar_t__ vmd_free_count; scalar_t__ vmd_pageout_free_min; scalar_t__ vmd_pageout_pages_needed; int /*<<< orphan*/  vmd_domain; scalar_t__ vmd_severeset; scalar_t__ vmd_minset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_CLR (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_domainset_lock ; 
 scalar_t__ vm_min_domains ; 
 scalar_t__ vm_min_waiters ; 
 scalar_t__ vm_pageproc_waiters ; 
 int /*<<< orphan*/  vm_paging_min (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_paging_severe (struct vm_domain*) ; 
 scalar_t__ vm_severe_domains ; 
 scalar_t__ vm_severe_waiters ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
vm_domain_clear(struct vm_domain *vmd)
{

	mtx_lock(&vm_domainset_lock);
	if (vmd->vmd_minset && !vm_paging_min(vmd)) {
		vmd->vmd_minset = 0;
		DOMAINSET_CLR(vmd->vmd_domain, &vm_min_domains);
		if (vm_min_waiters != 0) {
			vm_min_waiters = 0;
			wakeup(&vm_min_domains);
		}
	}
	if (vmd->vmd_severeset && !vm_paging_severe(vmd)) {
		vmd->vmd_severeset = 0;
		DOMAINSET_CLR(vmd->vmd_domain, &vm_severe_domains);
		if (vm_severe_waiters != 0) {
			vm_severe_waiters = 0;
			wakeup(&vm_severe_domains);
		}
	}

	/*
	 * If pageout daemon needs pages, then tell it that there are
	 * some free.
	 */
	if (vmd->vmd_pageout_pages_needed &&
	    vmd->vmd_free_count >= vmd->vmd_pageout_free_min) {
		wakeup(&vmd->vmd_pageout_pages_needed);
		vmd->vmd_pageout_pages_needed = 0;
	}

	/* See comments in vm_wait_doms(). */
	if (vm_pageproc_waiters) {
		vm_pageproc_waiters = 0;
		wakeup(&vm_pageproc_waiters);
	}
	mtx_unlock(&vm_domainset_lock);
}