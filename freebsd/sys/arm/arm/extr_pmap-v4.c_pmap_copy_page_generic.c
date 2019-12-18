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
typedef  int vm_paddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  pv_list; } ;
struct vm_page {TYPE_1__ md; } ;

/* Variables and functions */
 int L2_S_PROT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int L2_S_PROTO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct vm_page* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PTE_KERNEL ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int /*<<< orphan*/  bcopy_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* cdst_pte ; 
 int /*<<< orphan*/  cdstp ; 
 int /*<<< orphan*/  cmtx ; 
 int /*<<< orphan*/  cpu_cpwait () ; 
 int /*<<< orphan*/  cpu_dcache_inv_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_dcache_wbinv_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_l2cache_inv_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_tlb_flushD_SE (int /*<<< orphan*/ ) ; 
 int* csrc_pte ; 
 int /*<<< orphan*/  csrcp ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_clean_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pte_l2_s_cache_mode ; 

__attribute__((used)) static void
pmap_copy_page_generic(vm_paddr_t src, vm_paddr_t dst)
{
#if 0
	struct vm_page *src_pg = PHYS_TO_VM_PAGE(src);
#endif

	/*
	 * Clean the source page.  Hold the source page's lock for
	 * the duration of the copy so that no other mappings can
	 * be created while we have a potentially aliased mapping.
	 */
#if 0
	/*
	 * XXX: Not needed while we call cpu_dcache_wbinv_all() in
	 * pmap_copy_page().
	 */
	(void) pmap_clean_page(TAILQ_FIRST(&src_pg->md.pv_list), TRUE);
#endif
	/*
	 * Map the pages into the page hook points, copy them, and purge
	 * the cache for the appropriate page. Invalidate the TLB
	 * as required.
	 */
	mtx_lock(&cmtx);
	*csrc_pte = L2_S_PROTO | src |
	    L2_S_PROT(PTE_KERNEL, VM_PROT_READ) | pte_l2_s_cache_mode;
	PTE_SYNC(csrc_pte);
	*cdst_pte = L2_S_PROTO | dst |
	    L2_S_PROT(PTE_KERNEL, VM_PROT_WRITE) | pte_l2_s_cache_mode;
	PTE_SYNC(cdst_pte);
	cpu_tlb_flushD_SE(csrcp);
	cpu_tlb_flushD_SE(cdstp);
	cpu_cpwait();
	bcopy_page(csrcp, cdstp);
	mtx_unlock(&cmtx);
	cpu_dcache_inv_range(csrcp, PAGE_SIZE);
	cpu_dcache_wbinv_range(cdstp, PAGE_SIZE);
	cpu_l2cache_inv_range(csrcp, PAGE_SIZE);
	cpu_l2cache_wbinv_range(cdstp, PAGE_SIZE);
}