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
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_3__* pv_entry_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_11__ {int /*<<< orphan*/  pv_pmap; int /*<<< orphan*/  pv_va; } ;
struct TYPE_9__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_10__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGA_WRITEABLE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTBL_HOLD_FLAG (int /*<<< orphan*/ ) ; 
 TYPE_3__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_3__* TAILQ_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pv_link ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmu_booke_remove_all(mmu_t mmu, vm_page_t m)
{
	pv_entry_t pv, pvn;
	uint8_t hold_flag;

	rw_wlock(&pvh_global_lock);
	for (pv = TAILQ_FIRST(&m->md.pv_list); pv != NULL; pv = pvn) {
		pvn = TAILQ_NEXT(pv, pv_link);

		PMAP_LOCK(pv->pv_pmap);
		hold_flag = PTBL_HOLD_FLAG(pv->pv_pmap);
		pte_remove(mmu, pv->pv_pmap, pv->pv_va, hold_flag);
		PMAP_UNLOCK(pv->pv_pmap);
	}
	vm_page_aflag_clear(m, PGA_WRITEABLE);
	rw_wunlock(&pvh_global_lock);
}