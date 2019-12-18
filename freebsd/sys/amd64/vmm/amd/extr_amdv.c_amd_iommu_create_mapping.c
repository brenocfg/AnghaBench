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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static uint64_t
amd_iommu_create_mapping(void *domain, vm_paddr_t gpa, vm_paddr_t hpa,
			 uint64_t len)
{

	printf("amd_iommu_create_mapping: not implemented\n");
	return (0);
}