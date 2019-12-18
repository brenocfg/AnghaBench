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
typedef  int vm_size_t ;
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NBPDP ; 
 int NBPDR ; 
 int PG_PS ; 
 int /*<<< orphan*/  PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int X86_PG_V ; 
 int dmaplimit ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_demote_pde (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_demote_pdpe (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_pdpe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_pdpe_to_pde (int*,int /*<<< orphan*/ ) ; 
 int powerof2 (int) ; 

void
pmap_demote_DMAP(vm_paddr_t base, vm_size_t len, boolean_t invalidate)
{
	pdp_entry_t *pdpe;
	pd_entry_t *pde;
	vm_offset_t va;
	boolean_t changed;

	if (len == 0)
		return;
	KASSERT(powerof2(len), ("pmap_demote_DMAP: len is not a power of 2"));
	KASSERT((base & (len - 1)) == 0,
	    ("pmap_demote_DMAP: base is not a multiple of len"));
	if (len < NBPDP && base < dmaplimit) {
		va = PHYS_TO_DMAP(base);
		changed = FALSE;
		PMAP_LOCK(kernel_pmap);
		pdpe = pmap_pdpe(kernel_pmap, va);
		if ((*pdpe & X86_PG_V) == 0)
			panic("pmap_demote_DMAP: invalid PDPE");
		if ((*pdpe & PG_PS) != 0) {
			if (!pmap_demote_pdpe(kernel_pmap, pdpe, va))
				panic("pmap_demote_DMAP: PDPE failed");
			changed = TRUE;
		}
		if (len < NBPDR) {
			pde = pmap_pdpe_to_pde(pdpe, va);
			if ((*pde & X86_PG_V) == 0)
				panic("pmap_demote_DMAP: invalid PDE");
			if ((*pde & PG_PS) != 0) {
				if (!pmap_demote_pde(kernel_pmap, pde, va))
					panic("pmap_demote_DMAP: PDE failed");
				changed = TRUE;
			}
		}
		if (changed && invalidate)
			pmap_invalidate_page(kernel_pmap, va);
		PMAP_UNLOCK(kernel_pmap);
	}
}