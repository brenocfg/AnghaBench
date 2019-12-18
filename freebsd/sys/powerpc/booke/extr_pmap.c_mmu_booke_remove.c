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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  scalar_t__ pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK (scalar_t__) ; 
 scalar_t__ PMAP_REMOVE_DONE (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  PTBL_HOLD_FLAG (scalar_t__) ; 
 scalar_t__ PTE_ISVALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  VM_MAX_KERNEL_ADDRESS ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/ * pte_find (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_remove (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtual_avail ; 

__attribute__((used)) static void
mmu_booke_remove(mmu_t mmu, pmap_t pmap, vm_offset_t va, vm_offset_t endva)
{
	pte_t *pte;
	uint8_t hold_flag;

	int su = (pmap == kernel_pmap);

	//debugf("mmu_booke_remove: s (su = %d pmap=0x%08x tid=%d va=0x%08x endva=0x%08x)\n",
	//		su, (u_int32_t)pmap, pmap->pm_tid, va, endva);

	if (su) {
		KASSERT(((va >= virtual_avail) &&
		    (va <= VM_MAX_KERNEL_ADDRESS)),
		    ("mmu_booke_remove: kernel pmap, non kernel va"));
	} else {
		KASSERT((va <= VM_MAXUSER_ADDRESS),
		    ("mmu_booke_remove: user pmap, non user va"));
	}

	if (PMAP_REMOVE_DONE(pmap)) {
		//debugf("mmu_booke_remove: e (empty)\n");
		return;
	}

	hold_flag = PTBL_HOLD_FLAG(pmap);
	//debugf("mmu_booke_remove: hold_flag = %d\n", hold_flag);

	rw_wlock(&pvh_global_lock);
	PMAP_LOCK(pmap);
	for (; va < endva; va += PAGE_SIZE) {
		pte = pte_find(mmu, pmap, va);
		if ((pte != NULL) && PTE_ISVALID(pte))
			pte_remove(mmu, pmap, va, hold_flag);
	}
	PMAP_UNLOCK(pmap);
	rw_wunlock(&pvh_global_lock);

	//debugf("mmu_booke_remove: e\n");
}