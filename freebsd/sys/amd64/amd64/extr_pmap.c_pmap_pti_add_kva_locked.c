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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int X86_PG_A ; 
 int X86_PG_G ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int pg_nx ; 
 int pmap_cache_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pti_pde (int /*<<< orphan*/ ) ; 
 int* pmap_pti_pte (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pmap_pti_unwire_pde (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmap_pti_wire_pte (int*) ; 
 int /*<<< orphan*/  pte_store (int*,int) ; 
 int /*<<< orphan*/  pti_finalized ; 
 int /*<<< orphan*/  pti_obj ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunc_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_pti_add_kva_locked(vm_offset_t sva, vm_offset_t eva, bool exec)
{
	vm_paddr_t pa;
	pd_entry_t *pde;
	pt_entry_t *pte, ptev;
	bool unwire_pde;

	VM_OBJECT_ASSERT_WLOCKED(pti_obj);

	sva = trunc_page(sva);
	MPASS(sva > VM_MAXUSER_ADDRESS);
	eva = round_page(eva);
	MPASS(sva < eva);
	for (; sva < eva; sva += PAGE_SIZE) {
		pte = pmap_pti_pte(sva, &unwire_pde);
		pa = pmap_kextract(sva);
		ptev = pa | X86_PG_RW | X86_PG_V | X86_PG_A | X86_PG_G |
		    (exec ? 0 : pg_nx) | pmap_cache_bits(kernel_pmap,
		    VM_MEMATTR_DEFAULT, FALSE);
		if (*pte == 0) {
			pte_store(pte, ptev);
			pmap_pti_wire_pte(pte);
		} else {
			KASSERT(!pti_finalized,
			    ("pti overlap after fin %#lx %#lx %#lx",
			    sva, *pte, ptev));
			KASSERT(*pte == ptev,
			    ("pti non-identical pte after fin %#lx %#lx %#lx",
			    sva, *pte, ptev));
		}
		if (unwire_pde) {
			pde = pmap_pti_pde(sva);
			pmap_pti_unwire_pde(pde, true);
		}
	}
}