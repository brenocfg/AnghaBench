#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct TYPE_5__ {int /*<<< orphan*/  pat_mode; } ;
struct TYPE_6__ {int flags; TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pmap_change_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pmap_page_set_memattr(vm_page_t m, vm_memattr_t ma)
{

	m->md.pat_mode = ma;

	/*
	 * If "m" is a normal page, update its direct mapping.  This update
	 * can be relied upon to perform any cache operations that are
	 * required for data coherence.
	 */
	if ((m->flags & PG_FICTITIOUS) == 0 &&
	    pmap_change_attr(PHYS_TO_DMAP(VM_PAGE_TO_PHYS(m)), PAGE_SIZE,
	    m->md.pat_mode))
		panic("memory attribute change on the direct map failed");
}