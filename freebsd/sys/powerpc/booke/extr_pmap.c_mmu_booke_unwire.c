#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_7__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_8__ {TYPE_1__ pm_stats; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 scalar_t__ PTE_ISVALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTE_ISWIRED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTE_WIRED ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_find (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void
mmu_booke_unwire(mmu_t mmu, pmap_t pmap, vm_offset_t sva, vm_offset_t eva)
{
	vm_offset_t va;
	pte_t *pte;

	PMAP_LOCK(pmap);
	for (va = sva; va < eva; va += PAGE_SIZE) {
		if ((pte = pte_find(mmu, pmap, va)) != NULL &&
		    PTE_ISVALID(pte)) {
			if (!PTE_ISWIRED(pte))
				panic("mmu_booke_unwire: pte %p isn't wired",
				    pte);
			*pte &= ~PTE_WIRED;
			pmap->pm_stats.wired_count--;
		}
	}
	PMAP_UNLOCK(pmap);

}