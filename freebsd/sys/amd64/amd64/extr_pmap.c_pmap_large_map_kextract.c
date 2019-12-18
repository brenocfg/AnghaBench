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
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int pt_entry_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int AMDID_PAGE1GB ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_MASK ; 
 int PDPMASK ; 
 int PDRMASK ; 
 int PG_FRAME ; 
 int PG_PS_FRAME ; 
 int PG_PS_PDP_FRAME ; 
 int PMAP_ADDRESS_IN_LARGEMAP (int) ; 
 int X86_PG_PS ; 
 int X86_PG_V ; 
 int amd_feature ; 
 int* pmap_large_map_pdpe (int) ; 
 int* pmap_pde_to_pte (int*,int) ; 
 int* pmap_pdpe_to_pde (int*,int) ; 

__attribute__((used)) static vm_paddr_t
pmap_large_map_kextract(vm_offset_t va)
{
	pdp_entry_t *pdpe, pdp;
	pd_entry_t *pde, pd;
	pt_entry_t *pte, pt;

	KASSERT(PMAP_ADDRESS_IN_LARGEMAP(va),
	    ("not largemap range %#lx", (u_long)va));
	pdpe = pmap_large_map_pdpe(va);
	pdp = *pdpe;
	KASSERT((pdp & X86_PG_V) != 0,
	    ("invalid pdp va %#lx pdpe %#lx pdp %#lx", va,
	    (u_long)pdpe, pdp));
	if ((pdp & X86_PG_PS) != 0) {
		KASSERT((amd_feature & AMDID_PAGE1GB) != 0,
		    ("no 1G pages, va %#lx pdpe %#lx pdp %#lx", va,
		    (u_long)pdpe, pdp));
		return ((pdp & PG_PS_PDP_FRAME) | (va & PDPMASK));
	}
	pde = pmap_pdpe_to_pde(pdpe, va);
	pd = *pde;
	KASSERT((pd & X86_PG_V) != 0,
	    ("invalid pd va %#lx pde %#lx pd %#lx", va, (u_long)pde, pd));
	if ((pd & X86_PG_PS) != 0)
		return ((pd & PG_PS_FRAME) | (va & PDRMASK));
	pte = pmap_pde_to_pte(pde, va);
	pt = *pte;
	KASSERT((pt & X86_PG_V) != 0,
	    ("invalid pte va %#lx pte %#lx pt %#lx", va, (u_long)pte, pt));
	return ((pt & PG_FRAME) | (va & PAGE_MASK));
}