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
typedef  int u_long ;
struct pmap {int* pm_context; int /*<<< orphan*/  pm_active; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASI_DMMU_DEMAP ; 
 int /*<<< orphan*/  ASI_IMMU_DEMAP ; 
 scalar_t__ CPU_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KERNBASE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_STATS_INC (int /*<<< orphan*/ ) ; 
 int TLB_DEMAP_NUCLEUS ; 
 int TLB_DEMAP_PAGE ; 
 int TLB_DEMAP_PRIMARY ; 
 int TLB_DEMAP_VA (scalar_t__) ; 
 int /*<<< orphan*/  cpuid ; 
 size_t curcpu ; 
 int /*<<< orphan*/  flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 void* ipi_tlb_range_demap (struct pmap*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ipi_wait (void*) ; 
 struct pmap* kernel_pmap ; 
 int /*<<< orphan*/  stxa (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_nrange_demap ; 

void
tlb_range_demap(struct pmap *pm, vm_offset_t start, vm_offset_t end)
{
	vm_offset_t va;
	void *cookie;
	u_long flags;
	register_t s;

	PMAP_STATS_INC(tlb_nrange_demap);
	cookie = ipi_tlb_range_demap(pm, start, end);
	s = intr_disable();
	if (CPU_ISSET(PCPU_GET(cpuid), &pm->pm_active)) {
		KASSERT(pm->pm_context[curcpu] != -1,
		    ("tlb_range_demap: inactive pmap?"));
		if (pm == kernel_pmap)
			flags = TLB_DEMAP_NUCLEUS | TLB_DEMAP_PAGE;
		else
			flags = TLB_DEMAP_PRIMARY | TLB_DEMAP_PAGE;

		for (va = start; va < end; va += PAGE_SIZE) {
			stxa(TLB_DEMAP_VA(va) | flags, ASI_DMMU_DEMAP, 0);
			stxa(TLB_DEMAP_VA(va) | flags, ASI_IMMU_DEMAP, 0);
			flush(KERNBASE);
		}
	}
	intr_restore(s);
	ipi_wait(cookie);
}