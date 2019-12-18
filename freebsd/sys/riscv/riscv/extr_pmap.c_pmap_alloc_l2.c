#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int Ln_ENTRIES_SHIFT ; 
 scalar_t__ NUL2E ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int PTE_RWX ; 
 int /*<<< orphan*/  PTE_TO_PHYS (int) ; 
 TYPE_1__* _pmap_alloc_l3 (int /*<<< orphan*/ ,scalar_t__,struct rwlock**) ; 
 int /*<<< orphan*/ * pmap_l1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_l2_pindex (int /*<<< orphan*/ ) ; 
 int pmap_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
pmap_alloc_l2(pmap_t pmap, vm_offset_t va, struct rwlock **lockp)
{
	pd_entry_t *l1;
	vm_page_t l2pg;
	vm_pindex_t l2pindex;

retry:
	l1 = pmap_l1(pmap, va);
	if (l1 != NULL && (pmap_load(l1) & PTE_RWX) == 0) {
		/* Add a reference to the L2 page. */
		l2pg = PHYS_TO_VM_PAGE(PTE_TO_PHYS(pmap_load(l1)));
		l2pg->ref_count++;
	} else {
		/* Allocate a L2 page. */
		l2pindex = pmap_l2_pindex(va) >> Ln_ENTRIES_SHIFT;
		l2pg = _pmap_alloc_l3(pmap, NUL2E + l2pindex, lockp);
		if (l2pg == NULL && lockp != NULL)
			goto retry;
	}
	return (l2pg);
}