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
struct vm_domain {int vmd_minset; int vmd_severeset; int /*<<< orphan*/  vmd_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_domainset_lock ; 
 int /*<<< orphan*/  vm_min_domains ; 
 scalar_t__ vm_paging_min (struct vm_domain*) ; 
 scalar_t__ vm_paging_severe (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_severe_domains ; 

void
vm_domain_set(struct vm_domain *vmd)
{

	mtx_lock(&vm_domainset_lock);
	if (!vmd->vmd_minset && vm_paging_min(vmd)) {
		vmd->vmd_minset = 1;
		DOMAINSET_SET(vmd->vmd_domain, &vm_min_domains);
	}
	if (!vmd->vmd_severeset && vm_paging_severe(vmd)) {
		vmd->vmd_severeset = 1;
		DOMAINSET_SET(vmd->vmd_domain, &vm_severe_domains);
	}
	mtx_unlock(&vm_domainset_lock);
}