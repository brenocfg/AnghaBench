#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct l2_bucket {int* l2b_kva; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int boolean_t ;
struct TYPE_4__ {int pvh_attrs; } ;
struct TYPE_5__ {int oflags; TYPE_1__ md; } ;

/* Variables and functions */
 int L2_S_PROT_W ; 
 int MINCORE_INCORE ; 
 int MINCORE_MODIFIED ; 
 int MINCORE_MODIFIED_OTHER ; 
 int MINCORE_REFERENCED ; 
 int MINCORE_REFERENCED_OTHER ; 
 TYPE_2__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PVF_REF ; 
 int VPO_UNMANAGED ; 
 size_t l2pte_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2pte_pa (int) ; 
 int /*<<< orphan*/  l2pte_valid (int) ; 
 struct l2_bucket* pmap_get_l2_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pmap_mincore(pmap_t pmap, vm_offset_t addr, vm_paddr_t *pap)
{
	struct l2_bucket *l2b;
	pt_entry_t *ptep, pte;
	vm_paddr_t pa;
	vm_page_t m;
	int val;
	boolean_t managed;

	PMAP_LOCK(pmap);
	l2b = pmap_get_l2_bucket(pmap, addr);
        if (l2b == NULL) {
		PMAP_UNLOCK(pmap);
		return (0);
        }
	ptep = &l2b->l2b_kva[l2pte_index(addr)];
	pte = *ptep;
	if (!l2pte_valid(pte)) {
		PMAP_UNLOCK(pmap);
		return (0);
	}
	val = MINCORE_INCORE;
	if (pte & L2_S_PROT_W)
		val |= MINCORE_MODIFIED | MINCORE_MODIFIED_OTHER;
        managed = false;
	pa = l2pte_pa(pte);
        m = PHYS_TO_VM_PAGE(pa);
        if (m != NULL && !(m->oflags & VPO_UNMANAGED))
                managed = true;
	if (managed) {
		/*
		 * The ARM pmap tries to maintain a per-mapping
		 * reference bit.  The trouble is that it's kept in
		 * the PV entry, not the PTE, so it's costly to access
		 * here.  You would need to acquire the pvh global
		 * lock, call pmap_find_pv(), and introduce a custom
		 * version of vm_page_pa_tryrelock() that releases and
		 * reacquires the pvh global lock.  In the end, I
		 * doubt it's worthwhile.  This may falsely report
		 * the given address as referenced.
		 */
		if ((m->md.pvh_attrs & PVF_REF) != 0)
			val |= MINCORE_REFERENCED | MINCORE_REFERENCED_OTHER;
	}
	if ((val & (MINCORE_MODIFIED_OTHER | MINCORE_REFERENCED_OTHER)) !=
	    (MINCORE_MODIFIED_OTHER | MINCORE_REFERENCED_OTHER) && managed) {
		*pap = pa;
	}
	PMAP_UNLOCK(pmap);
	return (val);
}