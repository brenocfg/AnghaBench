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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int L1_C_ADDR_MASK ; 
 size_t L1_IDX (scalar_t__) ; 
 int L1_S_CACHE_MASK ; 
 int L2_S_CACHE_MASK ; 
 int /*<<< orphan*/  PTE_SYNC (int*) ; 
 int /*<<< orphan*/  cpu_dcache_wbinv_range (scalar_t__,int) ; 
 int /*<<< orphan*/  cpu_l2cache_wbinv_range (scalar_t__,int) ; 
 scalar_t__ kernel_pt_lookup (scalar_t__) ; 
 scalar_t__ l1pte_section_p (int) ; 
 size_t l2pte_index (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,int*) ; 
 int pte_l1_s_cache_mode_pt ; 
 int pte_l2_s_cache_mode_pt ; 

__attribute__((used)) static int
pmap_set_pt_cache_mode(pd_entry_t *kl1, vm_offset_t va)
{
	pd_entry_t *pdep, pde;
	pt_entry_t *ptep, pte;
	vm_offset_t pa;
	int rv = 0;

	/*
	 * Make sure the descriptor itself has the correct cache mode
	 */
	pdep = &kl1[L1_IDX(va)];
	pde = *pdep;

	if (l1pte_section_p(pde)) {
		if ((pde & L1_S_CACHE_MASK) != pte_l1_s_cache_mode_pt) {
			*pdep = (pde & ~L1_S_CACHE_MASK) |
			    pte_l1_s_cache_mode_pt;
			PTE_SYNC(pdep);
			cpu_dcache_wbinv_range((vm_offset_t)pdep,
			    sizeof(*pdep));
			cpu_l2cache_wbinv_range((vm_offset_t)pdep,
			    sizeof(*pdep));
			rv = 1;
		}
	} else {
		pa = (vm_paddr_t)(pde & L1_C_ADDR_MASK);
		ptep = (pt_entry_t *)kernel_pt_lookup(pa);
		if (ptep == NULL)
			panic("pmap_bootstrap: No L2 for L2 @ va %p\n", ptep);

		ptep = &ptep[l2pte_index(va)];
		pte = *ptep;
		if ((pte & L2_S_CACHE_MASK) != pte_l2_s_cache_mode_pt) {
			*ptep = (pte & ~L2_S_CACHE_MASK) |
			    pte_l2_s_cache_mode_pt;
			PTE_SYNC(ptep);
			cpu_dcache_wbinv_range((vm_offset_t)ptep,
			    sizeof(*ptep));
			cpu_l2cache_wbinv_range((vm_offset_t)ptep,
			    sizeof(*ptep));
			rv = 1;
		}
	}

	return (rv);
}