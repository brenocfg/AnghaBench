#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {int prot; int pa; } ;
struct pvo_entry {int /*<<< orphan*/  pvo_vaddr; TYPE_1__ pvo_pte; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int ADDR_POFF ; 
 int ENOENT ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVO_WIRED ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 struct pvo_entry* alloc_pvo_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pvo_entry (struct pvo_entry*) ; 
 int /*<<< orphan*/  init_pvo_entry (struct pvo_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int moea64_calc_wimg (int,int /*<<< orphan*/ ) ; 
 int moea64_pvo_enter (int /*<<< orphan*/ ,struct pvo_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pvo_entry* moea64_pvo_find_va (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_pvo_remove_from_page (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  moea64_pvo_remove_from_pmap (int /*<<< orphan*/ ,struct pvo_entry*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

void
moea64_kenter_attr(mmu_t mmu, vm_offset_t va, vm_paddr_t pa, vm_memattr_t ma)
{
	int		error;	
	struct pvo_entry *pvo, *oldpvo;

	do {
		pvo = alloc_pvo_entry(0);
		if (pvo == NULL)
			vm_wait(NULL);
	} while (pvo == NULL);
	pvo->pvo_pte.prot = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE;
	pvo->pvo_pte.pa = (pa & ~ADDR_POFF) | moea64_calc_wimg(pa, ma);
	pvo->pvo_vaddr |= PVO_WIRED;

	PMAP_LOCK(kernel_pmap);
	oldpvo = moea64_pvo_find_va(kernel_pmap, va);
	if (oldpvo != NULL)
		moea64_pvo_remove_from_pmap(mmu, oldpvo);
	init_pvo_entry(pvo, kernel_pmap, va);
	error = moea64_pvo_enter(mmu, pvo, NULL, NULL);
	PMAP_UNLOCK(kernel_pmap);

	/* Free any dead pages */
	if (oldpvo != NULL) {
		moea64_pvo_remove_from_page(mmu, oldpvo);
		free_pvo_entry(oldpvo);
	}

	if (error != 0 && error != ENOENT)
		panic("moea64_kenter: failed to enter va %#zx pa %#jx: %d", va,
		    (uintmax_t)pa, error);
}