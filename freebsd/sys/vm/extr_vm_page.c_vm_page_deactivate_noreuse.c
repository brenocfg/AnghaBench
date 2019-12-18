#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_5__ {int oflags; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  _vm_page_deactivate_noreuse (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_wired (TYPE_1__*) ; 

void
vm_page_deactivate_noreuse(vm_page_t m)
{

	KASSERT(m->object != NULL,
	    ("vm_page_deactivate_noreuse: page %p has no object", m));

	if ((m->oflags & VPO_UNMANAGED) == 0 && !vm_page_wired(m))
		_vm_page_deactivate_noreuse(m);
}