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
struct mem_affinity {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  all_domains ; 
 struct mem_affinity* mem_affinity ; 
 int* mem_locality ; 
 int vm_ndomains ; 

void
vm_phys_register_domains(int ndomains, struct mem_affinity *affinity,
    int *locality)
{
#ifdef NUMA
	int d, i;

	/*
	 * For now the only override value that we support is 1, which
	 * effectively disables NUMA-awareness in the allocators.
	 */
	d = 0;
	TUNABLE_INT_FETCH("vm.numa.disabled", &d);
	if (d)
		ndomains = 1;

	if (ndomains > 1) {
		vm_ndomains = ndomains;
		mem_affinity = affinity;
		mem_locality = locality;
	}

	for (i = 0; i < vm_ndomains; i++)
		DOMAINSET_SET(i, &all_domains);
#else
	(void)ndomains;
	(void)affinity;
	(void)locality;
#endif
}