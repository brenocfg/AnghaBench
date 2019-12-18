#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int ;
struct md_page {int /*<<< orphan*/  pv_list; } ;
typedef  TYPE_1__* pv_entry_t ;
typedef  int /*<<< orphan*/  pt1_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_4__ {int /*<<< orphan*/  pv_va; } ;

/* Variables and functions */
 int PMAP_ENTER_NORECLAIM ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_pv_entry (int /*<<< orphan*/ ,int) ; 
 struct md_page* pa_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_pa (int /*<<< orphan*/ ) ; 
 scalar_t__ pv_entry_count ; 
 scalar_t__ pv_entry_high_water ; 
 int /*<<< orphan*/  pv_next ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
pmap_pv_insert_pte1(pmap_t pmap, vm_offset_t va, pt1_entry_t pte1, u_int flags)
{
	struct md_page *pvh;
	pv_entry_t pv;
	bool noreclaim;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	noreclaim = (flags & PMAP_ENTER_NORECLAIM) != 0;
	if ((noreclaim && pv_entry_count >= pv_entry_high_water) ||
	    (pv = get_pv_entry(pmap, noreclaim)) == NULL)
		return (false);
	pv->pv_va = va;
	pvh = pa_to_pvh(pte1_pa(pte1));
	TAILQ_INSERT_TAIL(&pvh->pv_list, pv, pv_next);
	return (true);
}