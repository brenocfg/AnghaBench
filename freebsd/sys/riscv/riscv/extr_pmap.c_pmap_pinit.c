#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_10__ {int /*<<< orphan*/  pm_l1; } ;
struct TYPE_9__ {int pm_satp; int /*<<< orphan*/  pm_root; int /*<<< orphan*/ * pm_l1; int /*<<< orphan*/  pm_active; int /*<<< orphan*/  pm_stats; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_ZERO ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int SATP_MODE_SV39 ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  allpmaps ; 
 int /*<<< orphan*/  allpmaps_lock ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* kernel_pmap ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pagezero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_list ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vm_radix_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

int
pmap_pinit(pmap_t pmap)
{
	vm_paddr_t l1phys;
	vm_page_t l1pt;

	/*
	 * allocate the l1 page
	 */
	while ((l1pt = vm_page_alloc(NULL, 0xdeadbeef, VM_ALLOC_NORMAL |
	    VM_ALLOC_NOOBJ | VM_ALLOC_WIRED | VM_ALLOC_ZERO)) == NULL)
		vm_wait(NULL);

	l1phys = VM_PAGE_TO_PHYS(l1pt);
	pmap->pm_l1 = (pd_entry_t *)PHYS_TO_DMAP(l1phys);
	pmap->pm_satp = SATP_MODE_SV39 | (l1phys >> PAGE_SHIFT);

	if ((l1pt->flags & PG_ZERO) == 0)
		pagezero(pmap->pm_l1);

	bzero(&pmap->pm_stats, sizeof(pmap->pm_stats));

	CPU_ZERO(&pmap->pm_active);

	/* Install kernel pagetables */
	memcpy(pmap->pm_l1, kernel_pmap->pm_l1, PAGE_SIZE);

	/* Add to the list of all user pmaps */
	mtx_lock(&allpmaps_lock);
	LIST_INSERT_HEAD(&allpmaps, pmap, pm_list);
	mtx_unlock(&allpmaps_lock);

	vm_radix_init(&pmap->pm_root);

	return (1);
}