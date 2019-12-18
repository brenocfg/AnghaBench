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
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_4__ {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/ * KPTmap ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PG_A ; 
 int PG_M ; 
 int PG_RW ; 
 int PG_V ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 size_t i386_btop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagezero (void*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_invalidate_page_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kenter_pde (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pmap_remove_pt_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_update_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  trunc_4mpage (int /*<<< orphan*/ ) ; 
 scalar_t__ vtopte (int /*<<< orphan*/ ) ; 
 scalar_t__ workaround_erratum383 ; 

__attribute__((used)) static void
pmap_remove_kernel_pde(pmap_t pmap, pd_entry_t *pde, vm_offset_t va)
{
	pd_entry_t newpde;
	vm_paddr_t mptepa;
	vm_page_t mpte;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	mpte = pmap_remove_pt_page(pmap, va);
	if (mpte == NULL)
		panic("pmap_remove_kernel_pde: Missing pt page.");

	mptepa = VM_PAGE_TO_PHYS(mpte);
	newpde = mptepa | PG_M | PG_A | PG_RW | PG_V;

	/*
	 * If this page table page was unmapped by a promotion, then it
	 * contains valid mappings.  Zero it to invalidate those mappings.
	 */
	if (mpte->valid != 0)
		pagezero((void *)&KPTmap[i386_btop(trunc_4mpage(va))]);

	/*
	 * Remove the mapping.
	 */
	if (workaround_erratum383)
		pmap_update_pde(pmap, va, pde, newpde);
	else 
		pmap_kenter_pde(va, newpde);

	/*
	 * Invalidate the recursive mapping of the page table page.
	 */
	pmap_invalidate_page_int(pmap, (vm_offset_t)vtopte(va));
}