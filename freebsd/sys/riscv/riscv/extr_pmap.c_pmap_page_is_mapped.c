#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct rwlock {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  pv_list; } ;
struct TYPE_8__ {int oflags; int flags; TYPE_1__ md; } ;

/* Variables and functions */
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 struct rwlock* VM_PAGE_TO_PV_LIST_LOCK (TYPE_2__*) ; 
 int VPO_UNMANAGED ; 
 TYPE_4__* pa_to_pvh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_rlock (struct rwlock*) ; 
 int /*<<< orphan*/  rw_runlock (struct rwlock*) ; 

bool
pmap_page_is_mapped(vm_page_t m)
{
	struct rwlock *lock;
	bool rv;

	if ((m->oflags & VPO_UNMANAGED) != 0)
		return (false);
	lock = VM_PAGE_TO_PV_LIST_LOCK(m);
	rw_rlock(lock);
	rv = !TAILQ_EMPTY(&m->md.pv_list) ||
	    ((m->flags & PG_FICTITIOUS) == 0 &&
	    !TAILQ_EMPTY(&pa_to_pvh(VM_PAGE_TO_PHYS(m))->pv_list));
	rw_runlock(lock);
	return (rv);
}