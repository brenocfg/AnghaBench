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
struct pvo_entry {int pvo_vaddr; TYPE_1__ pvo_pte; int /*<<< orphan*/ * pvo_pmap; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct pvo_entry*,int /*<<< orphan*/ ) ; 
 int LPTE_RPGN ; 
 int PGA_EXECUTABLE ; 
 int PGA_WRITEABLE ; 
 int PVO_DEAD ; 
 int PVO_MANAGED ; 
 int /*<<< orphan*/  PV_LOCKASSERT (int) ; 
 int /*<<< orphan*/  STAT_MOEA64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_pvo_entries ; 
 int /*<<< orphan*/  moea64_pvo_remove_calls ; 
 int /*<<< orphan*/  pvo_vlink ; 
 int /*<<< orphan*/  vm_page_aflag_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_page_to_pvoh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
moea64_pvo_remove_from_page_locked(mmu_t mmu, struct pvo_entry *pvo,
    vm_page_t m)
{

	KASSERT(pvo->pvo_vaddr & PVO_DEAD, ("Trying to delink live page"));

	/* Use NULL pmaps as a sentinel for races in page deletion */
	if (pvo->pvo_pmap == NULL)
		return;
	pvo->pvo_pmap = NULL;

	/*
	 * Update vm about page writeability/executability if managed
	 */
	PV_LOCKASSERT(pvo->pvo_pte.pa & LPTE_RPGN);
	if (pvo->pvo_vaddr & PVO_MANAGED) {
		if (m != NULL) {
			LIST_REMOVE(pvo, pvo_vlink);
			if (LIST_EMPTY(vm_page_to_pvoh(m)))
				vm_page_aflag_clear(m,
				    PGA_WRITEABLE | PGA_EXECUTABLE);
		}
	}

	STAT_MOEA64(moea64_pvo_entries--);
	STAT_MOEA64(moea64_pvo_remove_calls++);
}