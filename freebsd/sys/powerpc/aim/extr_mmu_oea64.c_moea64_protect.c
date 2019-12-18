#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
struct pvo_entry {scalar_t__ pvo_vaddr; } ;
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_13__ {TYPE_1__* p_vmspace; } ;
struct TYPE_12__ {int /*<<< orphan*/  pmap_pvo; } ;
struct TYPE_11__ {TYPE_2__ vm_pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,TYPE_2__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 scalar_t__ PVO_VADDR (struct pvo_entry*) ; 
 struct pvo_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 struct pvo_entry* RB_NFIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pvo_entry*) ; 
 int VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 TYPE_7__* curproc ; 
 TYPE_2__* kernel_pmap ; 
 int /*<<< orphan*/  moea64_pvo_protect (int /*<<< orphan*/ ,TYPE_2__*,struct pvo_entry*,int) ; 
 int /*<<< orphan*/  moea64_remove (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pvo_tree ; 

void
moea64_protect(mmu_t mmu, pmap_t pm, vm_offset_t sva, vm_offset_t eva,
    vm_prot_t prot)
{
	struct	pvo_entry *pvo, *tpvo, key;

	CTR4(KTR_PMAP, "moea64_protect: pm=%p sva=%#x eva=%#x prot=%#x", pm,
	    sva, eva, prot);

	KASSERT(pm == &curproc->p_vmspace->vm_pmap || pm == kernel_pmap,
	    ("moea64_protect: non current pmap"));

	if ((prot & VM_PROT_READ) == VM_PROT_NONE) {
		moea64_remove(mmu, pm, sva, eva);
		return;
	}

	PMAP_LOCK(pm);
	key.pvo_vaddr = sva;
	for (pvo = RB_NFIND(pvo_tree, &pm->pmap_pvo, &key);
	    pvo != NULL && PVO_VADDR(pvo) < eva; pvo = tpvo) {
		tpvo = RB_NEXT(pvo_tree, &pm->pmap_pvo, pvo);
		moea64_pvo_protect(mmu, pm, pvo, prot);
	}
	PMAP_UNLOCK(pm);
}