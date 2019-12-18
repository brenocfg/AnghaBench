#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_long ;
struct tte {int /*<<< orphan*/  tte_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  resident_count; int /*<<< orphan*/  wired_count; } ;
struct pmap {TYPE_2__ pm_stats; } ;
struct TYPE_9__ {int /*<<< orphan*/  tte_list; } ;
struct TYPE_11__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 TYPE_3__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_REMOVE_DONE (struct pmap*) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tte*,int /*<<< orphan*/ ) ; 
 int TD_FAKE ; 
 int /*<<< orphan*/  TD_PA (int) ; 
 int TD_PV ; 
 int TD_REF ; 
 int TD_W ; 
 int TD_WIRED ; 
 int /*<<< orphan*/  TTE_ZERO (struct tte*) ; 
 int atomic_readandclear_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_cache_remove (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tte_link ; 
 int /*<<< orphan*/  tte_list_global_lock ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_3__*) ; 

int
pmap_remove_tte(struct pmap *pm, struct pmap *pm2, struct tte *tp,
    vm_offset_t va)
{
	vm_page_t m;
	u_long data;

	rw_assert(&tte_list_global_lock, RA_WLOCKED);
	data = atomic_readandclear_long(&tp->tte_data);
	if ((data & TD_FAKE) == 0) {
		m = PHYS_TO_VM_PAGE(TD_PA(data));
		TAILQ_REMOVE(&m->md.tte_list, tp, tte_link);
		if ((data & TD_WIRED) != 0)
			pm->pm_stats.wired_count--;
		if ((data & TD_PV) != 0) {
			if ((data & TD_W) != 0)
				vm_page_dirty(m);
			if ((data & TD_REF) != 0)
				vm_page_aflag_set(m, PGA_REFERENCED);
			if (TAILQ_EMPTY(&m->md.tte_list))
				vm_page_aflag_clear(m, PGA_WRITEABLE);
			pm->pm_stats.resident_count--;
		}
		pmap_cache_remove(m, va);
	}
	TTE_ZERO(tp);
	if (PMAP_REMOVE_DONE(pm))
		return (0);
	return (1);
}