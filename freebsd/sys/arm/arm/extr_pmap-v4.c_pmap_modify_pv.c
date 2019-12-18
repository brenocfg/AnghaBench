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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int ;
struct TYPE_8__ {int pvh_attrs; } ;
struct vm_page {TYPE_1__ md; } ;
struct pv_entry {int pv_flags; } ;
typedef  TYPE_3__* pmap_t ;
struct TYPE_9__ {int /*<<< orphan*/  wired_count; } ;
struct TYPE_10__ {TYPE_2__ pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_ASSERT_LOCKED (TYPE_3__*) ; 
 int PVF_MOD ; 
 int PVF_REF ; 
 int PVF_WIRED ; 
 int PVF_WRITE ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 struct pv_entry* pmap_find_pv (struct vm_page*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_fix_cache (struct vm_page*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
pmap_modify_pv(struct vm_page *pg, pmap_t pm, vm_offset_t va,
    u_int clr_mask, u_int set_mask)
{
	struct pv_entry *npv;
	u_int flags, oflags;

	PMAP_ASSERT_LOCKED(pm);
	rw_assert(&pvh_global_lock, RA_WLOCKED);
	if ((npv = pmap_find_pv(pg, pm, va)) == NULL)
		return (0);

	/*
	 * There is at least one VA mapping this page.
	 */

	if (clr_mask & (PVF_REF | PVF_MOD))
		pg->md.pvh_attrs |= set_mask & (PVF_REF | PVF_MOD);

	oflags = npv->pv_flags;
	npv->pv_flags = flags = (oflags & ~clr_mask) | set_mask;

	if ((flags ^ oflags) & PVF_WIRED) {
		if (flags & PVF_WIRED)
			++pm->pm_stats.wired_count;
		else
			--pm->pm_stats.wired_count;
	}

	if ((flags ^ oflags) & PVF_WRITE)
		pmap_fix_cache(pg, pm, 0);

	return (oflags);
}