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
typedef  int u64 ;

/* Variables and functions */
 int MMIO_SPTE_GEN_HIGH_MASK ; 
 int MMIO_SPTE_GEN_HIGH_START ; 
 int MMIO_SPTE_GEN_LOW_MASK ; 
 int MMIO_SPTE_GEN_LOW_START ; 
 int shadow_mmio_mask ; 

__attribute__((used)) static u64 get_mmio_spte_generation(u64 spte)
{
	u64 gen;

	spte &= ~shadow_mmio_mask;

	gen = (spte & MMIO_SPTE_GEN_LOW_MASK) >> MMIO_SPTE_GEN_LOW_START;
	gen |= (spte & MMIO_SPTE_GEN_HIGH_MASK) >> MMIO_SPTE_GEN_HIGH_START;
	return gen;
}