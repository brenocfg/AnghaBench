#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_7__ {int oflags; int flags; TYPE_1__ md; } ;

/* Variables and functions */
 int FALSE ; 
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int VPO_UNMANAGED ; 
 TYPE_4__* pa_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

boolean_t
pmap_page_is_mapped(vm_page_t m)
{
	boolean_t rv;

	if ((m->oflags & VPO_UNMANAGED) != 0)
		return (FALSE);
	rw_wlock(&pvh_global_lock);
	rv = !TAILQ_EMPTY(&m->md.pv_list) ||
	    ((m->flags & PG_FICTITIOUS) == 0 &&
	    !TAILQ_EMPTY(&pa_to_pvh(VM_PAGE_TO_PHYS(m))->pv_list));
	rw_wunlock(&pvh_global_lock);
	return (rv);
}