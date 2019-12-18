#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
struct TYPE_14__ {int /*<<< orphan*/  pte_lo; } ;
struct TYPE_12__ {TYPE_5__ pte; } ;
struct pvo_entry {scalar_t__ pvo_vaddr; TYPE_2__ pvo_pte; } ;
struct pte {int dummy; } ;
typedef  TYPE_3__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_15__ {TYPE_1__* p_vmspace; } ;
struct TYPE_13__ {int /*<<< orphan*/  pmap_pvo; } ;
struct TYPE_11__ {TYPE_3__ vm_pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  PTE_BR ; 
 int /*<<< orphan*/  PTE_PP ; 
 scalar_t__ PVO_VADDR (struct pvo_entry*) ; 
 struct pvo_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 struct pvo_entry* RB_NFIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 int VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 TYPE_8__* curproc ; 
 TYPE_3__* kernel_pmap ; 
 int /*<<< orphan*/  moea_pte_change (struct pte*,TYPE_5__*,scalar_t__) ; 
 struct pte* moea_pvo_to_pte (struct pvo_entry*,int) ; 
 int /*<<< orphan*/  moea_remove (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  moea_table_mutex ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  pvo_tree ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

void
moea_protect(mmu_t mmu, pmap_t pm, vm_offset_t sva, vm_offset_t eva,
    vm_prot_t prot)
{
	struct	pvo_entry *pvo, *tpvo, key;
	struct	pte *pt;

	KASSERT(pm == &curproc->p_vmspace->vm_pmap || pm == kernel_pmap,
	    ("moea_protect: non current pmap"));

	if ((prot & VM_PROT_READ) == VM_PROT_NONE) {
		moea_remove(mmu, pm, sva, eva);
		return;
	}

	rw_wlock(&pvh_global_lock);
	PMAP_LOCK(pm);
	key.pvo_vaddr = sva;
	for (pvo = RB_NFIND(pvo_tree, &pm->pmap_pvo, &key);
	    pvo != NULL && PVO_VADDR(pvo) < eva; pvo = tpvo) {
		tpvo = RB_NEXT(pvo_tree, &pm->pmap_pvo, pvo);

		/*
		 * Grab the PTE pointer before we diddle with the cached PTE
		 * copy.
		 */
		pt = moea_pvo_to_pte(pvo, -1);
		/*
		 * Change the protection of the page.
		 */
		pvo->pvo_pte.pte.pte_lo &= ~PTE_PP;
		pvo->pvo_pte.pte.pte_lo |= PTE_BR;

		/*
		 * If the PVO is in the page table, update that pte as well.
		 */
		if (pt != NULL) {
			moea_pte_change(pt, &pvo->pvo_pte.pte, pvo->pvo_vaddr);
			mtx_unlock(&moea_table_mutex);
		}
	}
	rw_wunlock(&pvh_global_lock);
	PMAP_UNLOCK(pm);
}