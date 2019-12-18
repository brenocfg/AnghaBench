#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct pv_entry {scalar_t__ pv_va; } ;
typedef  scalar_t__ physAddress_t ;
struct TYPE_7__ {scalar_t__** portal_ce_pa; scalar_t__** portal_ce_size; int* portal_ci_va; scalar_t__** portal_ci_pa; scalar_t__** portal_ci_size; int* portal_ce_va; } ;
struct TYPE_5__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_6__ {TYPE_1__ md; } ;

/* Variables and functions */
 size_t BM_PORTAL ; 
 int PAGE_MASK ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ PHYS_TO_DMAP (scalar_t__) ; 
 TYPE_2__* PHYS_TO_VM_PAGE (scalar_t__) ; 
 scalar_t__ PMAP_HAS_DMAP ; 
 size_t QM_PORTAL ; 
 struct pv_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_3__ XX_PInfo ; 
 scalar_t__ ccsrbar_pa ; 
 scalar_t__ ccsrbar_size ; 
 int ccsrbar_va ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

void *
XX_PhysToVirt(physAddress_t addr)
{
	struct pv_entry *pv;
	vm_page_t page;
	int cpu;

	/* Check CCSR */
	if (addr >= ccsrbar_pa && addr < ccsrbar_pa + ccsrbar_size)
		return ((void *)((vm_offset_t)(addr - ccsrbar_pa) +
		    ccsrbar_va));

	cpu = PCPU_GET(cpuid);

	/* Handle BMAN mappings */
	if ((addr >= XX_PInfo.portal_ce_pa[BM_PORTAL][cpu]) &&
	    (addr < XX_PInfo.portal_ce_pa[BM_PORTAL][cpu] +
	    XX_PInfo.portal_ce_size[BM_PORTAL][cpu]))
		return ((void *)(XX_PInfo.portal_ci_va[BM_PORTAL] +
		    (vm_offset_t)(addr - XX_PInfo.portal_ci_pa[BM_PORTAL][cpu])));

	if ((addr >= XX_PInfo.portal_ci_pa[BM_PORTAL][cpu]) &&
	    (addr < XX_PInfo.portal_ci_pa[BM_PORTAL][cpu] +
	    XX_PInfo.portal_ci_size[BM_PORTAL][cpu]))
		return ((void *)(XX_PInfo.portal_ci_va[BM_PORTAL] +
		    (vm_offset_t)(addr - XX_PInfo.portal_ci_pa[BM_PORTAL][cpu])));

	/* Handle QMAN mappings */
	if ((addr >= XX_PInfo.portal_ce_pa[QM_PORTAL][cpu]) &&
	    (addr < XX_PInfo.portal_ce_pa[QM_PORTAL][cpu] +
	    XX_PInfo.portal_ce_size[QM_PORTAL][cpu]))
		return ((void *)(XX_PInfo.portal_ce_va[QM_PORTAL] +
		    (vm_offset_t)(addr - XX_PInfo.portal_ce_pa[QM_PORTAL][cpu])));

	if ((addr >= XX_PInfo.portal_ci_pa[QM_PORTAL][cpu]) &&
	    (addr < XX_PInfo.portal_ci_pa[QM_PORTAL][cpu] +
	    XX_PInfo.portal_ci_size[QM_PORTAL][cpu]))
		return ((void *)(XX_PInfo.portal_ci_va[QM_PORTAL] +
		    (vm_offset_t)(addr - XX_PInfo.portal_ci_pa[QM_PORTAL][cpu])));

	page = PHYS_TO_VM_PAGE(addr);
	pv = TAILQ_FIRST(&page->md.pv_list);

	if (pv != NULL)
		return ((void *)(pv->pv_va + ((vm_offset_t)addr & PAGE_MASK)));

	if (PMAP_HAS_DMAP)
		return ((void *)(uintptr_t)PHYS_TO_DMAP(addr));

	printf("NetCommSW: "
	    "Unable to translate physical address 0x%09jx!\n", (uintmax_t)addr);

	return (NULL);
}