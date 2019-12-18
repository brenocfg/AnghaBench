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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
typedef  scalar_t__ pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_2__ {scalar_t__ td_pinned; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  pmap_invalidate_page_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* pmap_pte_quick (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_remove_pte (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,struct spglist*) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_remove_page(pmap_t pmap, vm_offset_t va, struct spglist *free)
{
	pt_entry_t *pte;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	KASSERT(curthread->td_pinned > 0, ("curthread not pinned"));
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	if ((pte = pmap_pte_quick(pmap, va)) == NULL || *pte == 0)
		return;
	pmap_remove_pte(pmap, pte, va, free);
	pmap_invalidate_page_int(pmap, va);
}