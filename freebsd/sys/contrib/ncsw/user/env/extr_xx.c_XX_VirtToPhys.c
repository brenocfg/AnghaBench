#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int physAddress_t ;
struct TYPE_2__ {scalar_t__* portal_ce_va; scalar_t__** portal_ce_size; scalar_t__** portal_ce_pa; scalar_t__* portal_ci_va; scalar_t__** portal_ci_size; scalar_t__** portal_ci_pa; } ;

/* Variables and functions */
 size_t BM_PORTAL ; 
 scalar_t__ DMAP_BASE_ADDRESS ; 
 scalar_t__ DMAP_MAX_ADDRESS ; 
 int DMAP_TO_PHYS (scalar_t__) ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_HAS_DMAP ; 
 size_t QM_PORTAL ; 
 TYPE_1__ XX_PInfo ; 
 scalar_t__ ccsrbar_pa ; 
 scalar_t__ ccsrbar_size ; 
 scalar_t__ ccsrbar_va ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ pmap_kextract (scalar_t__) ; 
 int /*<<< orphan*/  pmap_track_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,void*) ; 

physAddress_t
XX_VirtToPhys(void *addr)
{
	vm_paddr_t paddr;
	int cpu;

	cpu = PCPU_GET(cpuid);

	/* Handle NULL address */
	if (addr == NULL)
		return (-1);

	/* Check CCSR */
	if ((vm_offset_t)addr >= ccsrbar_va &&
	    (vm_offset_t)addr < ccsrbar_va + ccsrbar_size)
		return (((vm_offset_t)addr - ccsrbar_va) + ccsrbar_pa);

	/* Handle BMAN mappings */
	if (((vm_offset_t)addr >= XX_PInfo.portal_ce_va[BM_PORTAL]) &&
	    ((vm_offset_t)addr < XX_PInfo.portal_ce_va[BM_PORTAL] +
	    XX_PInfo.portal_ce_size[BM_PORTAL][cpu]))
		return (XX_PInfo.portal_ce_pa[BM_PORTAL][cpu] +
		    (vm_offset_t)addr - XX_PInfo.portal_ce_va[BM_PORTAL]);

	if (((vm_offset_t)addr >= XX_PInfo.portal_ci_va[BM_PORTAL]) &&
	    ((vm_offset_t)addr < XX_PInfo.portal_ci_va[BM_PORTAL] +
	    XX_PInfo.portal_ci_size[BM_PORTAL][cpu]))
		return (XX_PInfo.portal_ci_pa[BM_PORTAL][cpu] +
		    (vm_offset_t)addr - XX_PInfo.portal_ci_va[BM_PORTAL]);

	/* Handle QMAN mappings */
	if (((vm_offset_t)addr >= XX_PInfo.portal_ce_va[QM_PORTAL]) &&
	    ((vm_offset_t)addr < XX_PInfo.portal_ce_va[QM_PORTAL] +
	    XX_PInfo.portal_ce_size[QM_PORTAL][cpu]))
		return (XX_PInfo.portal_ce_pa[QM_PORTAL][cpu] +
		    (vm_offset_t)addr - XX_PInfo.portal_ce_va[QM_PORTAL]);

	if (((vm_offset_t)addr >= XX_PInfo.portal_ci_va[QM_PORTAL]) &&
	    ((vm_offset_t)addr < XX_PInfo.portal_ci_va[QM_PORTAL] +
	    XX_PInfo.portal_ci_size[QM_PORTAL][cpu]))
		return (XX_PInfo.portal_ci_pa[QM_PORTAL][cpu] +
		    (vm_offset_t)addr - XX_PInfo.portal_ci_va[QM_PORTAL]);

	if (PMAP_HAS_DMAP && (vm_offset_t)addr >= DMAP_BASE_ADDRESS &&
	    (vm_offset_t)addr <= DMAP_MAX_ADDRESS)
		return (DMAP_TO_PHYS((vm_offset_t)addr));
	else
		paddr = pmap_kextract((vm_offset_t)addr);

	if (paddr == 0)
		printf("NetCommSW: "
		    "Unable to translate virtual address %p!\n", addr);
	else
		pmap_track_page(kernel_pmap, (vm_offset_t)addr);

	return (paddr);
}