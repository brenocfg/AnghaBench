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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  invltlb () ; 
 int /*<<< orphan*/  invltlb_glob () ; 
 int /*<<< orphan*/ ** ipi_invltlb_counts ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  smp_tlb_done ; 
 int /*<<< orphan*/  smp_tlb_generation ; 
 scalar_t__ smp_tlb_pmap ; 
 int /*<<< orphan*/ * xhits_gbl ; 

void
invltlb_handler(void)
{
	uint32_t generation;
  
#ifdef COUNT_XINVLTLB_HITS
	xhits_gbl[PCPU_GET(cpuid)]++;
#endif /* COUNT_XINVLTLB_HITS */
#ifdef COUNT_IPIS
	(*ipi_invltlb_counts[PCPU_GET(cpuid)])++;
#endif /* COUNT_IPIS */

	/*
	 * Reading the generation here allows greater parallelism
	 * since invalidating the TLB is a serializing operation.
	 */
	generation = smp_tlb_generation;
	if (smp_tlb_pmap == kernel_pmap)
		invltlb_glob();
#ifdef __amd64__
	else
		invltlb();
#endif
	PCPU_SET(smp_tlb_done, generation);
}