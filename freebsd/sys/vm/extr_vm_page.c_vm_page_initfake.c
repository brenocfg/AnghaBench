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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct TYPE_5__ {int flags; int ref_count; int /*<<< orphan*/  busy_lock; int /*<<< orphan*/  oflags; int /*<<< orphan*/  queue; int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  PQ_NONE ; 
 int /*<<< orphan*/  VPB_SINGLE_EXCLUSIVER ; 
 int /*<<< orphan*/  VPO_UNMANAGED ; 
 int /*<<< orphan*/  pmap_page_init (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_page_set_memattr (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
vm_page_initfake(vm_page_t m, vm_paddr_t paddr, vm_memattr_t memattr)
{

	if ((m->flags & PG_FICTITIOUS) != 0) {
		/*
		 * The page's memattr might have changed since the
		 * previous initialization.  Update the pmap to the
		 * new memattr.
		 */
		goto memattr;
	}
	m->phys_addr = paddr;
	m->queue = PQ_NONE;
	/* Fictitious pages don't use "segind". */
	m->flags = PG_FICTITIOUS;
	/* Fictitious pages don't use "order" or "pool". */
	m->oflags = VPO_UNMANAGED;
	m->busy_lock = VPB_SINGLE_EXCLUSIVER;
	/* Fictitious pages are unevictable. */
	m->ref_count = 1;
	pmap_page_init(m);
memattr:
	pmap_page_set_memattr(m, memattr);
}