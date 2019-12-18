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
struct TYPE_6__ {int oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PVF_WRITE ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  pmap_clearbit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_page_is_write_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_1__*) ; 

void
pmap_remove_write(vm_page_t m)
{

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("pmap_remove_write: page %p is not managed", m));
	vm_page_assert_busied(m);

	if (pmap_page_is_write_mapped(m))
		pmap_clearbit(m, PVF_WRITE);
}