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
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int vm_offset_t ;
struct TYPE_2__ {int prot; int pa; } ;
struct pvo_entry {TYPE_1__ pvo_pte; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int ADDR_POFF ; 
 int LPTE_RPGN ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 struct pvo_entry* moea64_pvo_find_va (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_page_wire_mapped (int /*<<< orphan*/ *) ; 

vm_page_t
moea64_extract_and_hold(mmu_t mmu, pmap_t pmap, vm_offset_t va, vm_prot_t prot)
{
	struct	pvo_entry *pvo;
	vm_page_t m;
        
	m = NULL;
	PMAP_LOCK(pmap);
	pvo = moea64_pvo_find_va(pmap, va & ~ADDR_POFF);
	if (pvo != NULL && (pvo->pvo_pte.prot & prot) == prot) {
		m = PHYS_TO_VM_PAGE(pvo->pvo_pte.pa & LPTE_RPGN);
		if (!vm_page_wire_mapped(m))
			m = NULL;
	}
	PMAP_UNLOCK(pmap);
	return (m);
}