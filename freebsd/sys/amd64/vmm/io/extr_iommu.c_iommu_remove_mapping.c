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
 size_t IOMMU_REMOVE_MAPPING (void*,int /*<<< orphan*/ ,size_t) ; 

void
iommu_remove_mapping(void *dom, vm_paddr_t gpa, size_t len)
{
	uint64_t unmapped, remaining;

	remaining = len;

	while (remaining > 0) {
		unmapped = IOMMU_REMOVE_MAPPING(dom, gpa, remaining);
		gpa += unmapped;
		remaining -= unmapped;
	}
}