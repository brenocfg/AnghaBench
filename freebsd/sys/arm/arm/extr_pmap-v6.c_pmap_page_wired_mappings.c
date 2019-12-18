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
typedef  TYPE_1__* vm_page_t ;
struct TYPE_4__ {int oflags; int flags; int /*<<< orphan*/  md; } ;

/* Variables and functions */
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/ * pa_to_pvh (int /*<<< orphan*/ ) ; 
 int pmap_pvh_wired_mappings (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

int
pmap_page_wired_mappings(vm_page_t m)
{
	int count;

	count = 0;
	if ((m->oflags & VPO_UNMANAGED) != 0)
		return (count);
	rw_wlock(&pvh_global_lock);
	count = pmap_pvh_wired_mappings(&m->md, count);
	if ((m->flags & PG_FICTITIOUS) == 0) {
		count = pmap_pvh_wired_mappings(pa_to_pvh(VM_PAGE_TO_PHYS(m)),
		    count);
	}
	rw_wunlock(&pvh_global_lock);
	return (count);
}