#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct pvo_head {int dummy; } ;
struct pvo_entry {int /*<<< orphan*/  pvo_pmap; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_8__ {int aflags; } ;

/* Variables and functions */
 struct pvo_entry* LIST_FIRST (struct pvo_head*) ; 
 struct pvo_entry* LIST_NEXT (struct pvo_entry*,int /*<<< orphan*/ ) ; 
 int PGA_WRITEABLE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_CHG ; 
 int /*<<< orphan*/  moea_attr_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea_pvo_remove (struct pvo_entry*,int) ; 
 scalar_t__ moea_query_bit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  pvo_vlink ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_1__*) ; 
 struct pvo_head* vm_page_to_pvoh (TYPE_1__*) ; 

void
moea_remove_all(mmu_t mmu, vm_page_t m)
{
	struct  pvo_head *pvo_head;
	struct	pvo_entry *pvo, *next_pvo;
	pmap_t	pmap;

	rw_wlock(&pvh_global_lock);
	pvo_head = vm_page_to_pvoh(m);
	for (pvo = LIST_FIRST(pvo_head); pvo != NULL; pvo = next_pvo) {
		next_pvo = LIST_NEXT(pvo, pvo_vlink);

		pmap = pvo->pvo_pmap;
		PMAP_LOCK(pmap);
		moea_pvo_remove(pvo, -1);
		PMAP_UNLOCK(pmap);
	}
	if ((m->aflags & PGA_WRITEABLE) && moea_query_bit(m, PTE_CHG)) {
		moea_attr_clear(m, PTE_CHG);
		vm_page_dirty(m);
	}
	vm_page_aflag_clear(m, PGA_WRITEABLE);
	rw_wunlock(&pvh_global_lock);
}