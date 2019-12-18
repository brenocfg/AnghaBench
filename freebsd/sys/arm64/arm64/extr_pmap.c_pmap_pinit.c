#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  TYPE_3__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_7__ {scalar_t__ rt_root; } ;
struct TYPE_9__ {int /*<<< orphan*/  pm_cookie; int /*<<< orphan*/  pm_stats; TYPE_1__ pm_root; int /*<<< orphan*/ * pm_l0; int /*<<< orphan*/  pm_l0_paddr; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  COOKIE_FROM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int PG_ZERO ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pagezero (int /*<<< orphan*/ *) ; 
 TYPE_2__* vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

int
pmap_pinit(pmap_t pmap)
{
	vm_page_t l0pt;

	/*
	 * allocate the l0 page
	 */
	while ((l0pt = vm_page_alloc(NULL, 0, VM_ALLOC_NORMAL |
	    VM_ALLOC_NOOBJ | VM_ALLOC_WIRED | VM_ALLOC_ZERO)) == NULL)
		vm_wait(NULL);

	pmap->pm_l0_paddr = VM_PAGE_TO_PHYS(l0pt);
	pmap->pm_l0 = (pd_entry_t *)PHYS_TO_DMAP(pmap->pm_l0_paddr);

	if ((l0pt->flags & PG_ZERO) == 0)
		pagezero(pmap->pm_l0);

	pmap->pm_root.rt_root = 0;
	bzero(&pmap->pm_stats, sizeof(pmap->pm_stats));
	pmap->pm_cookie = COOKIE_FROM(-1, INT_MAX);

	return (1);
}