#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct TYPE_12__ {int prot; int pa; } ;
struct pvo_entry {int pvo_vaddr; TYPE_1__ pvo_pte; } ;
typedef  TYPE_5__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int int64_t ;
struct TYPE_14__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_16__ {TYPE_3__ pm_stats; int /*<<< orphan*/  pmap_pvo; } ;
struct TYPE_13__ {int /*<<< orphan*/  mdpg_attrs; } ;
struct TYPE_15__ {TYPE_2__ md; } ;

/* Variables and functions */
 int LPTE_CHG ; 
 int LPTE_REF ; 
 int LPTE_RPGN ; 
 int MOEA64_PTE_REPLACE (int /*<<< orphan*/ ,struct pvo_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 TYPE_4__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_5__*) ; 
 int PVO_MANAGED ; 
 scalar_t__ PVO_VADDR (struct pvo_entry*) ; 
 int PVO_WIRED ; 
 struct pvo_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 struct pvo_entry* RB_NFIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 int VM_PROT_WRITE ; 
 int atomic_readandclear_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,struct pvo_entry*) ; 
 int /*<<< orphan*/  pvo_tree ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_4__*) ; 

void
moea64_unwire(mmu_t mmu, pmap_t pm, vm_offset_t sva, vm_offset_t eva)
{
	struct	pvo_entry key, *pvo;
	vm_page_t m;
	int64_t	refchg;

	key.pvo_vaddr = sva;
	PMAP_LOCK(pm);
	for (pvo = RB_NFIND(pvo_tree, &pm->pmap_pvo, &key);
	    pvo != NULL && PVO_VADDR(pvo) < eva;
	    pvo = RB_NEXT(pvo_tree, &pm->pmap_pvo, pvo)) {
		if ((pvo->pvo_vaddr & PVO_WIRED) == 0)
			panic("moea64_unwire: pvo %p is missing PVO_WIRED",
			    pvo);
		pvo->pvo_vaddr &= ~PVO_WIRED;
		refchg = MOEA64_PTE_REPLACE(mmu, pvo, 0 /* No invalidation */);
		if ((pvo->pvo_vaddr & PVO_MANAGED) &&
		    (pvo->pvo_pte.prot & VM_PROT_WRITE)) {
			if (refchg < 0)
				refchg = LPTE_CHG;
			m = PHYS_TO_VM_PAGE(pvo->pvo_pte.pa & LPTE_RPGN);

			refchg |= atomic_readandclear_32(&m->md.mdpg_attrs);
			if (refchg & LPTE_CHG)
				vm_page_dirty(m);
			if (refchg & LPTE_REF)
				vm_page_aflag_set(m, PGA_REFERENCED);
		}
		pm->pm_stats.wired_count--;
	}
	PMAP_UNLOCK(pm);
}