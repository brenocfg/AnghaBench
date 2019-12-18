#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
typedef  int pt_entry_t ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_7__ {int wired_count; int resident_count; } ;
struct TYPE_8__ {TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int PG_A ; 
 int PG_FRAME ; 
 int PG_G ; 
 int PG_M ; 
 int PG_MANAGED ; 
 int PG_RW ; 
 int PG_W ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_invalidate_page_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_remove_entry (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_unuse_pt (TYPE_2__*,int /*<<< orphan*/ ,struct spglist*) ; 
 int pte_load_clear (int*) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmap_remove_pte(pmap_t pmap, pt_entry_t *ptq, vm_offset_t va,
    struct spglist *free)
{
	pt_entry_t oldpte;
	vm_page_t m;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	oldpte = pte_load_clear(ptq);
	KASSERT(oldpte != 0,
	    ("pmap_remove_pte: pmap %p va %x zero pte", pmap, va));
	if (oldpte & PG_W)
		pmap->pm_stats.wired_count -= 1;
	/*
	 * Machines that don't support invlpg, also don't support
	 * PG_G.
	 */
	if (oldpte & PG_G)
		pmap_invalidate_page_int(kernel_pmap, va);
	pmap->pm_stats.resident_count -= 1;
	if (oldpte & PG_MANAGED) {
		m = PHYS_TO_VM_PAGE(oldpte & PG_FRAME);
		if ((oldpte & (PG_M | PG_RW)) == (PG_M | PG_RW))
			vm_page_dirty(m);
		if (oldpte & PG_A)
			vm_page_aflag_set(m, PGA_REFERENCED);
		pmap_remove_entry(pmap, m, va);
	}
	return (pmap_unuse_pt(pmap, va, free));
}