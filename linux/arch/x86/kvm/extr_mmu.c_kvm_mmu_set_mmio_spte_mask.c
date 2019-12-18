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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ SPTE_MMIO_MASK ; 
 scalar_t__ SPTE_SPECIAL_MASK ; 
 scalar_t__ shadow_mmio_access_mask ; 
 scalar_t__ shadow_mmio_mask ; 
 scalar_t__ shadow_mmio_value ; 

void kvm_mmu_set_mmio_spte_mask(u64 mmio_mask, u64 mmio_value, u64 access_mask)
{
	BUG_ON((u64)(unsigned)access_mask != access_mask);
	BUG_ON((mmio_mask & mmio_value) != mmio_value);
	shadow_mmio_value = mmio_value | SPTE_MMIO_MASK;
	shadow_mmio_mask = mmio_mask | SPTE_SPECIAL_MASK;
	shadow_mmio_access_mask = access_mask;
}