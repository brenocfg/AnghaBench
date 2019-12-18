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
typedef  int /*<<< orphan*/  vm_paddr_t ;

/* Variables and functions */
 void* IOMMU_CREATE_DOMAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpset_int (int volatile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int volatile*,int) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  iommu_init () ; 

void *
iommu_create_domain(vm_paddr_t maxaddr)
{
	static volatile int iommu_initted;

	if (iommu_initted < 2) {
		if (atomic_cmpset_int(&iommu_initted, 0, 1)) {
			iommu_init();
			atomic_store_rel_int(&iommu_initted, 2);
		} else
			while (iommu_initted == 1)
				cpu_spinwait();
	}
	return (IOMMU_CREATE_DOMAIN(maxaddr));
}