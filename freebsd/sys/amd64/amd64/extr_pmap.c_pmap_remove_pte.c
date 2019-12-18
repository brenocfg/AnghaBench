#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
struct md_page {int /*<<< orphan*/  pv_list; } ;
typedef  int pt_entry_t ;
typedef  TYPE_3__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_21__ {int wired_count; } ;
struct TYPE_23__ {TYPE_1__ pm_stats; } ;
struct TYPE_20__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_22__ {int flags; TYPE_11__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_PV_LIST_LOCK_TO_VM_PAGE (struct rwlock**,TYPE_2__*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 int PG_FICTITIOUS ; 
 int PG_FRAME ; 
 int PG_MANAGED ; 
 int PG_W ; 
 TYPE_2__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 struct md_page* pa_to_pvh (int /*<<< orphan*/ ) ; 
 int pmap_accessed_bit (TYPE_3__*) ; 
 int /*<<< orphan*/  pmap_delayed_invl_page (TYPE_2__*) ; 
 int pmap_modified_bit (TYPE_3__*) ; 
 int /*<<< orphan*/  pmap_pvh_free (TYPE_11__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_resident_count_dec (TYPE_3__*,int) ; 
 int pmap_rw_bit (TYPE_3__*) ; 
 int pmap_unuse_pt (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spglist*) ; 
 int pte_load_clear (int*) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_2__*) ; 

__attribute__((used)) static int
pmap_remove_pte(pmap_t pmap, pt_entry_t *ptq, vm_offset_t va, 
    pd_entry_t ptepde, struct spglist *free, struct rwlock **lockp)
{
	struct md_page *pvh;
	pt_entry_t oldpte, PG_A, PG_M, PG_RW;
	vm_page_t m;

	PG_A = pmap_accessed_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	oldpte = pte_load_clear(ptq);
	if (oldpte & PG_W)
		pmap->pm_stats.wired_count -= 1;
	pmap_resident_count_dec(pmap, 1);
	if (oldpte & PG_MANAGED) {
		m = PHYS_TO_VM_PAGE(oldpte & PG_FRAME);
		if ((oldpte & (PG_M | PG_RW)) == (PG_M | PG_RW))
			vm_page_dirty(m);
		if (oldpte & PG_A)
			vm_page_aflag_set(m, PGA_REFERENCED);
		CHANGE_PV_LIST_LOCK_TO_VM_PAGE(lockp, m);
		pmap_pvh_free(&m->md, pmap, va);
		if (TAILQ_EMPTY(&m->md.pv_list) &&
		    (m->flags & PG_FICTITIOUS) == 0) {
			pvh = pa_to_pvh(VM_PAGE_TO_PHYS(m));
			if (TAILQ_EMPTY(&pvh->pv_list))
				vm_page_aflag_clear(m, PGA_WRITEABLE);
		}
		pmap_delayed_invl_page(m);
	}
	return (pmap_unuse_pt(pmap, va, ptepde, free));
}