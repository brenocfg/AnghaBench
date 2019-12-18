#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_3__* pv_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  pv_va; } ;
struct TYPE_8__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_9__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* get_pv_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pv_list ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
pmap_try_insert_pv_entry(pmap_t pmap, vm_page_t mpte, vm_offset_t va,
    vm_page_t m)
{
	pv_entry_t pv;

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	if ((pv = get_pv_entry(pmap, TRUE)) != NULL) {
		pv->pv_va = va;
		TAILQ_INSERT_TAIL(&m->md.pv_list, pv, pv_list);
		return (TRUE);
	} else
		return (FALSE);
}