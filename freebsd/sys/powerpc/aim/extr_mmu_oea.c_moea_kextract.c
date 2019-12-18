#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
struct TYPE_3__ {int pte_lo; } ;
struct TYPE_4__ {TYPE_1__ pte; } ;
struct pvo_entry {TYPE_2__ pvo_pte; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int ADDR_POFF ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PTE_RPGN ; 
 int VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  kernel_pmap ; 
 struct pvo_entry* moea_pvo_find_va (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

vm_paddr_t
moea_kextract(mmu_t mmu, vm_offset_t va)
{
	struct		pvo_entry *pvo;
	vm_paddr_t pa;

	/*
	 * Allow direct mappings on 32-bit OEA
	 */
	if (va < VM_MIN_KERNEL_ADDRESS) {
		return (va);
	}

	PMAP_LOCK(kernel_pmap);
	pvo = moea_pvo_find_va(kernel_pmap, va & ~ADDR_POFF, NULL);
	KASSERT(pvo != NULL, ("moea_kextract: no addr found"));
	pa = (pvo->pvo_pte.pte.pte_lo & PTE_RPGN) | (va & ADDR_POFF);
	PMAP_UNLOCK(kernel_pmap);
	return (pa);
}