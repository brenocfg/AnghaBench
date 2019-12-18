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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int EFAULT ; 
 int TLB1_ENTRIES ; 
 scalar_t__ tlb1_iomapped (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mmu_booke_dev_direct_mapped(mmu_t mmu, vm_paddr_t pa, vm_size_t size)
{
	int i;
	vm_offset_t va;

	/*
	 * This currently does not work for entries that
	 * overlap TLB1 entries.
	 */
	for (i = 0; i < TLB1_ENTRIES; i ++) {
		if (tlb1_iomapped(i, pa, size, &va) == 0)
			return (0);
	}

	return (EFAULT);
}