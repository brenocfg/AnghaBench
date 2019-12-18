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
struct vm_domain {scalar_t__ vmd_free_count; scalar_t__ vmd_pageout_free_min; int vmd_pageout_pages_needed; int /*<<< orphan*/  vmd_domain; } ;
typedef  int /*<<< orphan*/  domainset_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DOMAINSET_ZERO (int /*<<< orphan*/ *) ; 
 int PDROP ; 
 int PSWP ; 
 struct vm_domain* VM_DOMAIN (int) ; 
 int /*<<< orphan*/ * curproc ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pageproc ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vm_domain_free_assert_unlocked (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domainset_lock ; 
 int /*<<< orphan*/  vm_wait_doms (int /*<<< orphan*/ *) ; 

void
vm_wait_domain(int domain)
{
	struct vm_domain *vmd;
	domainset_t wdom;

	vmd = VM_DOMAIN(domain);
	vm_domain_free_assert_unlocked(vmd);

	if (curproc == pageproc) {
		mtx_lock(&vm_domainset_lock);
		if (vmd->vmd_free_count < vmd->vmd_pageout_free_min) {
			vmd->vmd_pageout_pages_needed = 1;
			msleep(&vmd->vmd_pageout_pages_needed,
			    &vm_domainset_lock, PDROP | PSWP, "VMWait", 0);
		} else
			mtx_unlock(&vm_domainset_lock);
	} else {
		if (pageproc == NULL)
			panic("vm_wait in early boot");
		DOMAINSET_ZERO(&wdom);
		DOMAINSET_SET(vmd->vmd_domain, &wdom);
		vm_wait_doms(&wdom);
	}
}