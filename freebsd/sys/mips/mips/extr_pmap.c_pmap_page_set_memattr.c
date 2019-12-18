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
typedef  int vm_memattr_t ;
struct TYPE_4__ {int pv_flags; int /*<<< orphan*/  pv_list; } ;
struct TYPE_5__ {TYPE_1__ md; } ;

/* Variables and functions */
 int PV_MEMATTR_MASK ; 
 int PV_MEMATTR_SHIFT ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
pmap_page_set_memattr(vm_page_t m, vm_memattr_t ma)
{

	/*
	 * It appears that this function can only be called before any mappings
	 * for the page are established.  If this ever changes, this code will
	 * need to walk the pv_list and make each of the existing mappings
	 * uncacheable, being careful to sync caches and PTEs (and maybe
	 * invalidate TLB?) for any current mapping it modifies.
	 */
	if (TAILQ_FIRST(&m->md.pv_list) != NULL)
		panic("Can't change memattr on page with existing mappings");

	/* Clean memattr portion of pv_flags */
	m->md.pv_flags &= ~PV_MEMATTR_MASK;
	m->md.pv_flags |= (ma << PV_MEMATTR_SHIFT) & PV_MEMATTR_MASK;
}