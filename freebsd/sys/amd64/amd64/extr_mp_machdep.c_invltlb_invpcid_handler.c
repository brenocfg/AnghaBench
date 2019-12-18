#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct invpcid_descr {scalar_t__ addr; scalar_t__ pad; int /*<<< orphan*/  pcid; } ;
struct TYPE_5__ {TYPE_1__* pm_pcids; } ;
struct TYPE_4__ {int /*<<< orphan*/  pm_pcid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVPCID_CTX ; 
 int /*<<< orphan*/  INVPCID_CTXGLOB ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  invpcid (struct invpcid_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** ipi_invltlb_counts ; 
 TYPE_2__* kernel_pmap ; 
 int /*<<< orphan*/  smp_tlb_done ; 
 int /*<<< orphan*/  smp_tlb_generation ; 
 TYPE_2__* smp_tlb_pmap ; 
 int /*<<< orphan*/ * xhits_gbl ; 

void
invltlb_invpcid_handler(void)
{
	struct invpcid_descr d;
	uint32_t generation;

#ifdef COUNT_XINVLTLB_HITS
	xhits_gbl[PCPU_GET(cpuid)]++;
#endif /* COUNT_XINVLTLB_HITS */
#ifdef COUNT_IPIS
	(*ipi_invltlb_counts[PCPU_GET(cpuid)])++;
#endif /* COUNT_IPIS */

	generation = smp_tlb_generation;
	d.pcid = smp_tlb_pmap->pm_pcids[PCPU_GET(cpuid)].pm_pcid;
	d.pad = 0;
	d.addr = 0;
	invpcid(&d, smp_tlb_pmap == kernel_pmap ? INVPCID_CTXGLOB :
	    INVPCID_CTX);
	PCPU_SET(smp_tlb_done, generation);
}