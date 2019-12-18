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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPI_INVLRNG ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  ipi_range ; 
 int ipi_range_size ; 
 scalar_t__ smp_started ; 
 int /*<<< orphan*/  smp_targeted_tlb_shootdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void
smp_masked_invlpg_range(cpuset_t mask, vm_offset_t addr1, vm_offset_t addr2,
    pmap_t pmap)
{

	if (smp_started) {
		smp_targeted_tlb_shootdown(mask, IPI_INVLRNG, pmap,
		    addr1, addr2);
#ifdef COUNT_XINVLTLB_HITS
		ipi_range++;
		ipi_range_size += (addr2 - addr1) / PAGE_SIZE;
#endif
	}
}