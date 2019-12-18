#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mdpg_pvoh; } ;
struct vm_page {TYPE_4__ md; } ;
struct TYPE_10__ {int pte_lo; } ;
struct TYPE_8__ {TYPE_5__ pte; } ;
struct pvo_entry {int pvo_vaddr; TYPE_3__ pvo_pte; TYPE_2__* pvo_pmap; } ;
struct pte {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  wired_count; int /*<<< orphan*/  resident_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  pmap_pvo; TYPE_1__ pm_stats; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct pvo_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 struct vm_page* PHYS_TO_VM_PAGE (int) ; 
 int PTE_CHG ; 
 int PTE_REF ; 
 int PTE_RPGN ; 
 int PVO_BOOTSTRAP ; 
 int PVO_MANAGED ; 
 int /*<<< orphan*/  PVO_PTEGIDX_CLR (struct pvo_entry*) ; 
 int PVO_WIRED ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 int /*<<< orphan*/  moea_attr_save (struct vm_page*,int) ; 
 int /*<<< orphan*/  moea_mpvo_zone ; 
 int /*<<< orphan*/  moea_pte_overflow ; 
 int /*<<< orphan*/  moea_pte_unset (struct pte*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  moea_pvo_entries ; 
 int /*<<< orphan*/  moea_pvo_remove_calls ; 
 struct pte* moea_pvo_to_pte (struct pvo_entry*,int) ; 
 int /*<<< orphan*/  moea_table_mutex ; 
 int /*<<< orphan*/  moea_upvo_zone ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvo_olink ; 
 int /*<<< orphan*/  pvo_tree ; 
 int /*<<< orphan*/  pvo_vlink ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (struct vm_page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
moea_pvo_remove(struct pvo_entry *pvo, int pteidx)
{
	struct	pte *pt;

	/*
	 * If there is an active pte entry, we need to deactivate it (and
	 * save the ref & cfg bits).
	 */
	pt = moea_pvo_to_pte(pvo, pteidx);
	if (pt != NULL) {
		moea_pte_unset(pt, &pvo->pvo_pte.pte, pvo->pvo_vaddr);
		mtx_unlock(&moea_table_mutex);
		PVO_PTEGIDX_CLR(pvo);
	} else {
		moea_pte_overflow--;
	}

	/*
	 * Update our statistics.
	 */
	pvo->pvo_pmap->pm_stats.resident_count--;
	if (pvo->pvo_vaddr & PVO_WIRED)
		pvo->pvo_pmap->pm_stats.wired_count--;

	/*
	 * Remove this PVO from the PV and pmap lists.
	 */
	LIST_REMOVE(pvo, pvo_vlink);
	RB_REMOVE(pvo_tree, &pvo->pvo_pmap->pmap_pvo, pvo);

	/*
	 * Save the REF/CHG bits into their cache if the page is managed.
	 * Clear PGA_WRITEABLE if all mappings of the page have been removed.
	 */
	if ((pvo->pvo_vaddr & PVO_MANAGED) == PVO_MANAGED) {
		struct vm_page *pg;

		pg = PHYS_TO_VM_PAGE(pvo->pvo_pte.pte.pte_lo & PTE_RPGN);
		if (pg != NULL) {
			moea_attr_save(pg, pvo->pvo_pte.pte.pte_lo &
			    (PTE_REF | PTE_CHG));
			if (LIST_EMPTY(&pg->md.mdpg_pvoh))
				vm_page_aflag_clear(pg, PGA_WRITEABLE);
		}
	}

	/*
	 * Remove this from the overflow list and return it to the pool
	 * if we aren't going to reuse it.
	 */
	LIST_REMOVE(pvo, pvo_olink);
	if (!(pvo->pvo_vaddr & PVO_BOOTSTRAP))
		uma_zfree(pvo->pvo_vaddr & PVO_MANAGED ? moea_mpvo_zone :
		    moea_upvo_zone, pvo);
	moea_pvo_entries--;
	moea_pvo_remove_calls++;
}