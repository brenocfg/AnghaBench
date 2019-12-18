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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int ATTR_MASK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int) ; 
 TYPE_1__* _pmap_alloc_l3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rwlock**) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int* pmap_l0_to_l1 (int*,int /*<<< orphan*/ ) ; 
 int* pmap_l1_to_l2 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_l2_pindex (int /*<<< orphan*/ ) ; 
 int pmap_load (int*) ; 
 int* pmap_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static vm_page_t
pmap_alloc_l3(pmap_t pmap, vm_offset_t va, struct rwlock **lockp)
{
	vm_pindex_t ptepindex;
	pd_entry_t *pde, tpde;
#ifdef INVARIANTS
	pt_entry_t *pte;
#endif
	vm_page_t m;
	int lvl;

	/*
	 * Calculate pagetable page index
	 */
	ptepindex = pmap_l2_pindex(va);
retry:
	/*
	 * Get the page directory entry
	 */
	pde = pmap_pde(pmap, va, &lvl);

	/*
	 * If the page table page is mapped, we just increment the hold count,
	 * and activate it. If we get a level 2 pde it will point to a level 3
	 * table.
	 */
	switch (lvl) {
	case -1:
		break;
	case 0:
#ifdef INVARIANTS
		pte = pmap_l0_to_l1(pde, va);
		KASSERT(pmap_load(pte) == 0,
		    ("pmap_alloc_l3: TODO: l0 superpages"));
#endif
		break;
	case 1:
#ifdef INVARIANTS
		pte = pmap_l1_to_l2(pde, va);
		KASSERT(pmap_load(pte) == 0,
		    ("pmap_alloc_l3: TODO: l1 superpages"));
#endif
		break;
	case 2:
		tpde = pmap_load(pde);
		if (tpde != 0) {
			m = PHYS_TO_VM_PAGE(tpde & ~ATTR_MASK);
			m->ref_count++;
			return (m);
		}
		break;
	default:
		panic("pmap_alloc_l3: Invalid level %d", lvl);
	}

	/*
	 * Here if the pte page isn't mapped, or if it has been deallocated.
	 */
	m = _pmap_alloc_l3(pmap, ptepindex, lockp);
	if (m == NULL && lockp != NULL)
		goto retry;

	return (m);
}