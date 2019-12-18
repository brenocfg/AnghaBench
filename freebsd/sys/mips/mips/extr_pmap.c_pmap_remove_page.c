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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct pmap {int dummy; } ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  scalar_t__ pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (struct pmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_V ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  pmap_invalidate_page (struct pmap*,int /*<<< orphan*/ ) ; 
 scalar_t__* pmap_pde (struct pmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pde_to_pte (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_remove_pte (struct pmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pte_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_remove_page(struct pmap *pmap, vm_offset_t va)
{
	pd_entry_t *pde;
	pt_entry_t *ptq;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	pde = pmap_pde(pmap, va);
	if (pde == NULL || *pde == 0)
		return;
	ptq = pmap_pde_to_pte(pde, va);

	/*
	 * If there is no pte for this address, just skip it!
	 */
	if (!pte_test(ptq, PTE_V))
		return;

	(void)pmap_remove_pte(pmap, ptq, va, *pde);
	pmap_invalidate_page(pmap, va);
}