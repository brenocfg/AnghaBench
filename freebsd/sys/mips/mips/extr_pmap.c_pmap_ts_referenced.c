#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct TYPE_4__ {int pv_flags; } ;
struct TYPE_5__ {int oflags; TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PV_TABLE_REF ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

int
pmap_ts_referenced(vm_page_t m)
{

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("pmap_ts_referenced: page %p is not managed", m));
	if (m->md.pv_flags & PV_TABLE_REF) {
		rw_wlock(&pvh_global_lock);
		m->md.pv_flags &= ~PV_TABLE_REF;
		rw_wunlock(&pvh_global_lock);
		return (1);
	}
	return (0);
}