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
typedef  size_t uint64_t ;

/* Variables and functions */
 size_t IOMMU_CREATE_MAPPING (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void
iommu_create_mapping(void *dom, vm_paddr_t gpa, vm_paddr_t hpa, size_t len)
{
	uint64_t mapped, remaining;

	remaining = len;

	while (remaining > 0) {
		mapped = IOMMU_CREATE_MAPPING(dom, gpa, hpa, remaining);
		gpa += mapped;
		hpa += mapped;
		remaining -= mapped;
	}
}