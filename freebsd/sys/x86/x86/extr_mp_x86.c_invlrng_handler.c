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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  invlpg (scalar_t__) ; 
 int /*<<< orphan*/ ** ipi_invlrng_counts ; 
 scalar_t__ kernel_pmap ; 
 scalar_t__ smp_tlb_addr1 ; 
 scalar_t__ smp_tlb_addr2 ; 
 int /*<<< orphan*/  smp_tlb_done ; 
 int /*<<< orphan*/  smp_tlb_generation ; 
 scalar_t__ smp_tlb_pmap ; 
 int /*<<< orphan*/ * xhits_rng ; 

void
invlrng_handler(void)
{
	vm_offset_t addr, addr2;
	uint32_t generation;

#ifdef COUNT_XINVLTLB_HITS
	xhits_rng[PCPU_GET(cpuid)]++;
#endif /* COUNT_XINVLTLB_HITS */
#ifdef COUNT_IPIS
	(*ipi_invlrng_counts[PCPU_GET(cpuid)])++;
#endif /* COUNT_IPIS */

	addr = smp_tlb_addr1;
	addr2 = smp_tlb_addr2;
	generation = smp_tlb_generation;	/* Overlap with serialization */
#ifdef __i386__
	if (smp_tlb_pmap == kernel_pmap)
#endif
		do {
			invlpg(addr);
			addr += PAGE_SIZE;
		} while (addr < addr2);

	PCPU_SET(smp_tlb_done, generation);
}