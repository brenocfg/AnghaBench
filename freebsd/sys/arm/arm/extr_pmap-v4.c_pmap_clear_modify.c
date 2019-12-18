#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct TYPE_7__ {int pvh_attrs; } ;
struct TYPE_8__ {int oflags; TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PVF_MOD ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  pmap_clearbit (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pmap_page_is_write_mapped (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_assert_busied (TYPE_2__*) ; 

void
pmap_clear_modify(vm_page_t m)
{

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("pmap_clear_modify: page %p is not managed", m));
	vm_page_assert_busied(m);

	if (!pmap_page_is_write_mapped(m))
		return;
	if (m->md.pvh_attrs & PVF_MOD)
		pmap_clearbit(m, PVF_MOD);
}