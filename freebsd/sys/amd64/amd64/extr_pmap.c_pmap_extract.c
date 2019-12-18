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
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PDPMASK ; 
 int PDRMASK ; 
 int PG_FRAME ; 
 int PG_PS ; 
 int PG_PS_FRAME ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int* pmap_pde_to_pte (int*,int) ; 
 int* pmap_pdpe (int /*<<< orphan*/ ,int) ; 
 int* pmap_pdpe_to_pde (int*,int) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 

vm_paddr_t 
pmap_extract(pmap_t pmap, vm_offset_t va)
{
	pdp_entry_t *pdpe;
	pd_entry_t *pde;
	pt_entry_t *pte, PG_V;
	vm_paddr_t pa;

	pa = 0;
	PG_V = pmap_valid_bit(pmap);
	PMAP_LOCK(pmap);
	pdpe = pmap_pdpe(pmap, va);
	if (pdpe != NULL && (*pdpe & PG_V) != 0) {
		if ((*pdpe & PG_PS) != 0)
			pa = (*pdpe & PG_PS_FRAME) | (va & PDPMASK);
		else {
			pde = pmap_pdpe_to_pde(pdpe, va);
			if ((*pde & PG_V) != 0) {
				if ((*pde & PG_PS) != 0) {
					pa = (*pde & PG_PS_FRAME) |
					    (va & PDRMASK);
				} else {
					pte = pmap_pde_to_pte(pde, va);
					pa = (*pte & PG_FRAME) |
					    (va & PAGE_MASK);
				}
			}
		}
	}
	PMAP_UNLOCK(pmap);
	return (pa);
}