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
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t NBPDR ; 
 size_t PAGE_SIZE ; 
 int PDRMASK ; 
 int PG_MANAGED ; 
 int PG_PROMOTED ; 
 int PG_PS_FRAME ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  atomic_cmpset_long (int*,int,int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int pg_nx ; 
 int pmap_global_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_pde_page (int /*<<< orphan*/ ,int,int) ; 
 int pmap_modified_bit (int /*<<< orphan*/ ) ; 
 int pmap_rw_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
pmap_protect_pde(pmap_t pmap, pd_entry_t *pde, vm_offset_t sva, vm_prot_t prot)
{
	pd_entry_t newpde, oldpde;
	vm_page_t m, mt;
	boolean_t anychanged;
	pt_entry_t PG_G, PG_M, PG_RW;

	PG_G = pmap_global_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	KASSERT((sva & PDRMASK) == 0,
	    ("pmap_protect_pde: sva is not 2mpage aligned"));
	anychanged = FALSE;
retry:
	oldpde = newpde = *pde;
	if ((prot & VM_PROT_WRITE) == 0) {
		if ((oldpde & (PG_MANAGED | PG_M | PG_RW)) ==
		    (PG_MANAGED | PG_M | PG_RW)) {
			m = PHYS_TO_VM_PAGE(oldpde & PG_PS_FRAME);
			for (mt = m; mt < &m[NBPDR / PAGE_SIZE]; mt++)
				vm_page_dirty(mt);
		}
		newpde &= ~(PG_RW | PG_M);
	}
	if ((prot & VM_PROT_EXECUTE) == 0)
		newpde |= pg_nx;
	if (newpde != oldpde) {
		/*
		 * As an optimization to future operations on this PDE, clear
		 * PG_PROMOTED.  The impending invalidation will remove any
		 * lingering 4KB page mappings from the TLB.
		 */
		if (!atomic_cmpset_long(pde, oldpde, newpde & ~PG_PROMOTED))
			goto retry;
		if ((oldpde & PG_G) != 0)
			pmap_invalidate_pde_page(kernel_pmap, sva, oldpde);
		else
			anychanged = TRUE;
	}
	return (anychanged);
}