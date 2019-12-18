#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_4__ {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (scalar_t__,int /*<<< orphan*/ ) ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int X86_PG_A ; 
 int X86_PG_M ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  pagezero (void*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pde_store (int*,int) ; 
 int /*<<< orphan*/  pmap_invalidate_page (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* pmap_remove_pt_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_update_pde (scalar_t__,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ vtopte (int /*<<< orphan*/ ) ; 
 scalar_t__ workaround_erratum383 ; 

__attribute__((used)) static void
pmap_remove_kernel_pde(pmap_t pmap, pd_entry_t *pde, vm_offset_t va)
{
	pd_entry_t newpde;
	vm_paddr_t mptepa;
	vm_page_t mpte;

	KASSERT(pmap == kernel_pmap, ("pmap %p is not kernel_pmap", pmap));
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	mpte = pmap_remove_pt_page(pmap, va);
	if (mpte == NULL)
		panic("pmap_remove_kernel_pde: Missing pt page.");

	mptepa = VM_PAGE_TO_PHYS(mpte);
	newpde = mptepa | X86_PG_M | X86_PG_A | X86_PG_RW | X86_PG_V;

	/*
	 * If this page table page was unmapped by a promotion, then it
	 * contains valid mappings.  Zero it to invalidate those mappings.
	 */
	if (mpte->valid != 0)
		pagezero((void *)PHYS_TO_DMAP(mptepa));

	/*
	 * Demote the mapping.
	 */
	if (workaround_erratum383)
		pmap_update_pde(pmap, va, pde, newpde);
	else
		pde_store(pde, newpde);

	/*
	 * Invalidate a stale recursive mapping of the page table page.
	 */
	pmap_invalidate_page(pmap, (vm_offset_t)vtopte(va));
}