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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct vm_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blacklist_head ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_domain_free_lock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_free_unlock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_freecnt_inc (struct vm_domain*,int) ; 
 struct vm_domain* vm_pagequeue_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_phys_paddr_to_vm_page (scalar_t__) ; 
 int vm_phys_unfree_page (int /*<<< orphan*/ *) ; 

bool
vm_page_blacklist_add(vm_paddr_t pa, bool verbose)
{
	struct vm_domain *vmd;
	vm_page_t m;
	int ret;

	m = vm_phys_paddr_to_vm_page(pa);
	if (m == NULL)
		return (true); /* page does not exist, no failure */

	vmd = vm_pagequeue_domain(m);
	vm_domain_free_lock(vmd);
	ret = vm_phys_unfree_page(m);
	vm_domain_free_unlock(vmd);
	if (ret != 0) {
		vm_domain_freecnt_inc(vmd, -1);
		TAILQ_INSERT_TAIL(&blacklist_head, m, listq);
		if (verbose)
			printf("Skipping page with pa 0x%jx\n", (uintmax_t)pa);
	}
	return (ret);
}