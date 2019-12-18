#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_6__ {int flags; int oflags; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PG_FICTITIOUS ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (TYPE_1__*) ; 
 int vm_page_wired (TYPE_1__*) ; 

__attribute__((used)) static void
ttm_vm_page_free(vm_page_t m)
{

	KASSERT(m->object == NULL, ("ttm page %p is owned", m));
	KASSERT(vm_page_wired(m), ("ttm lost wire %p", m));
	KASSERT((m->flags & PG_FICTITIOUS) != 0, ("ttm lost fictitious %p", m));
	KASSERT((m->oflags & VPO_UNMANAGED) == 0, ("ttm got unmanaged %p", m));
	m->flags &= ~PG_FICTITIOUS;
	m->oflags |= VPO_UNMANAGED;
	vm_page_unwire_noq(m);
	vm_page_free(m);
}