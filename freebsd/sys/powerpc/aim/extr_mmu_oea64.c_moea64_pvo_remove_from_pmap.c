#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mdpg_attrs; } ;
struct vm_page {TYPE_3__ md; } ;
struct TYPE_6__ {int prot; int pa; } ;
struct pvo_entry {int pvo_vaddr; TYPE_2__ pvo_pte; TYPE_4__* pvo_pmap; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  wired_count; int /*<<< orphan*/  resident_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  pmap_pvo; TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LPTE_CHG ; 
 int LPTE_REF ; 
 int LPTE_RPGN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MOEA64_PTE_UNSET (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 struct vm_page* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int PVO_DEAD ; 
 int PVO_MANAGED ; 
 int PVO_WIRED ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 int VM_PROT_WRITE ; 
 int atomic_readandclear_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvo_tree ; 
 int /*<<< orphan*/  vm_page_aflag_set (struct vm_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (struct vm_page*) ; 

__attribute__((used)) static void
moea64_pvo_remove_from_pmap(mmu_t mmu, struct pvo_entry *pvo)
{
	struct	vm_page *pg;
	int32_t refchg;

	KASSERT(pvo->pvo_pmap != NULL, ("Trying to remove PVO with no pmap"));
	PMAP_LOCK_ASSERT(pvo->pvo_pmap, MA_OWNED);
	KASSERT(!(pvo->pvo_vaddr & PVO_DEAD), ("Trying to remove dead PVO"));

	/*
	 * If there is an active pte entry, we need to deactivate it
	 */
	refchg = MOEA64_PTE_UNSET(mmu, pvo);
	if (refchg < 0) {
		/*
		 * If it was evicted from the page table, be pessimistic and
		 * dirty the page.
		 */
		if (pvo->pvo_pte.prot & VM_PROT_WRITE)
			refchg = LPTE_CHG;
		else
			refchg = 0;
	}

	/*
	 * Update our statistics.
	 */
	pvo->pvo_pmap->pm_stats.resident_count--;
	if (pvo->pvo_vaddr & PVO_WIRED)
		pvo->pvo_pmap->pm_stats.wired_count--;

	/*
	 * Remove this PVO from the pmap list.
	 */
	RB_REMOVE(pvo_tree, &pvo->pvo_pmap->pmap_pvo, pvo);

	/*
	 * Mark this for the next sweep
	 */
	pvo->pvo_vaddr |= PVO_DEAD;

	/* Send RC bits to VM */
	if ((pvo->pvo_vaddr & PVO_MANAGED) &&
	    (pvo->pvo_pte.prot & VM_PROT_WRITE)) {
		pg = PHYS_TO_VM_PAGE(pvo->pvo_pte.pa & LPTE_RPGN);
		if (pg != NULL) {
			refchg |= atomic_readandclear_32(&pg->md.mdpg_attrs);
			if (refchg & LPTE_CHG)
				vm_page_dirty(pg);
			if (refchg & LPTE_REF)
				vm_page_aflag_set(pg, PGA_REFERENCED);
		}
	}
}