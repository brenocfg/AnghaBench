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
typedef  int /*<<< orphan*/ * vm_page_t ;
struct TYPE_2__ {int pa; } ;
struct pvo_entry {int pvo_vaddr; TYPE_1__ pvo_pte; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int LPTE_RPGN ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int) ; 
 int PVO_MANAGED ; 
 int /*<<< orphan*/  PV_LOCK (int) ; 
 int /*<<< orphan*/  PV_UNLOCK (int) ; 
 int /*<<< orphan*/  moea64_pvo_remove_from_page_locked (int /*<<< orphan*/ ,struct pvo_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
moea64_pvo_remove_from_page(mmu_t mmu, struct pvo_entry *pvo)
{
	vm_page_t pg = NULL;

	if (pvo->pvo_vaddr & PVO_MANAGED)
		pg = PHYS_TO_VM_PAGE(pvo->pvo_pte.pa & LPTE_RPGN);

	PV_LOCK(pvo->pvo_pte.pa & LPTE_RPGN);
	moea64_pvo_remove_from_page_locked(mmu, pvo, pg);
	PV_UNLOCK(pvo->pvo_pte.pa & LPTE_RPGN);
}