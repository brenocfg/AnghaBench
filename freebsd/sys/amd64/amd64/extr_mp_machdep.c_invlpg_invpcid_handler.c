#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct invpcid_descr {int pcid; int /*<<< orphan*/  addr; scalar_t__ pad; } ;
struct TYPE_4__ {scalar_t__ pm_ucr3; TYPE_1__* pm_pcids; } ;
struct TYPE_3__ {int pm_pcid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVPCID_ADDR ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_NO_CR3 ; 
 int PMAP_PCID_USER_PT ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  invlpg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invpcid (struct invpcid_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** ipi_invlpg_counts ; 
 int /*<<< orphan*/  smp_tlb_addr1 ; 
 int /*<<< orphan*/  smp_tlb_done ; 
 int /*<<< orphan*/  smp_tlb_generation ; 
 TYPE_2__* smp_tlb_pmap ; 
 int /*<<< orphan*/ * xhits_pg ; 

void
invlpg_invpcid_handler(void)
{
	struct invpcid_descr d;
	uint32_t generation;

#ifdef COUNT_XINVLTLB_HITS
	xhits_pg[PCPU_GET(cpuid)]++;
#endif /* COUNT_XINVLTLB_HITS */
#ifdef COUNT_IPIS
	(*ipi_invlpg_counts[PCPU_GET(cpuid)])++;
#endif /* COUNT_IPIS */

	generation = smp_tlb_generation;	/* Overlap with serialization */
	invlpg(smp_tlb_addr1);
	if (smp_tlb_pmap->pm_ucr3 != PMAP_NO_CR3) {
		d.pcid = smp_tlb_pmap->pm_pcids[PCPU_GET(cpuid)].pm_pcid |
		    PMAP_PCID_USER_PT;
		d.pad = 0;
		d.addr = smp_tlb_addr1;
		invpcid(&d, INVPCID_ADDR);
	}
	PCPU_SET(smp_tlb_done, generation);
}