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
typedef  scalar_t__ vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_global_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int* pmap_pde_to_pte (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ pmap_remove_pte (int /*<<< orphan*/ ,int*,scalar_t__,int /*<<< orphan*/ ,struct spglist*,struct rwlock**) ; 

__attribute__((used)) static bool
pmap_remove_ptes(pmap_t pmap, vm_offset_t sva, vm_offset_t eva,
    pd_entry_t *pde, struct spglist *free, struct rwlock **lockp)
{
	pt_entry_t PG_G, *pte;
	vm_offset_t va;
	bool anyvalid;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	PG_G = pmap_global_bit(pmap);
	anyvalid = false;
	va = eva;
	for (pte = pmap_pde_to_pte(pde, sva); sva != eva; pte++,
	    sva += PAGE_SIZE) {
		if (*pte == 0) {
			if (va != eva) {
				pmap_invalidate_range(pmap, va, sva);
				va = eva;
			}
			continue;
		}
		if ((*pte & PG_G) == 0)
			anyvalid = true;
		else if (va == eva)
			va = sva;
		if (pmap_remove_pte(pmap, pte, sva, *pde, free, lockp)) {
			sva += PAGE_SIZE;
			break;
		}
	}
	if (va != eva)
		pmap_invalidate_range(pmap, va, sva);
	return (anyvalid);
}