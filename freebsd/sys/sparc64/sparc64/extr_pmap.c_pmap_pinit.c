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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct tte {int dummy; } ;
typedef  TYPE_3__* pmap_t ;
struct TYPE_9__ {int* pm_context; int /*<<< orphan*/  pm_stats; struct tte* pm_tsb; int /*<<< orphan*/ * pm_tsb_obj; int /*<<< orphan*/  pm_active; } ;
struct TYPE_7__ {TYPE_3__* pmap; } ;
struct TYPE_8__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int MAXCPU ; 
 int /*<<< orphan*/  OBJT_PHYS ; 
 int /*<<< orphan*/  TSB_BSIZE ; 
 int TSB_PAGES ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 scalar_t__ kva_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_qenter (int /*<<< orphan*/ ,TYPE_2__**,int) ; 
 int /*<<< orphan*/ * vm_object_allocate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_page_grab_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__**,int) ; 

int
pmap_pinit(pmap_t pm)
{
	vm_page_t ma[TSB_PAGES];
	int i;

	/*
	 * Allocate KVA space for the TSB.
	 */
	if (pm->pm_tsb == NULL) {
		pm->pm_tsb = (struct tte *)kva_alloc(TSB_BSIZE);
		if (pm->pm_tsb == NULL)
			return (0);
		}

	/*
	 * Allocate an object for it.
	 */
	if (pm->pm_tsb_obj == NULL)
		pm->pm_tsb_obj = vm_object_allocate(OBJT_PHYS, TSB_PAGES);

	for (i = 0; i < MAXCPU; i++)
		pm->pm_context[i] = -1;
	CPU_ZERO(&pm->pm_active);

	VM_OBJECT_WLOCK(pm->pm_tsb_obj);
	(void)vm_page_grab_pages(pm->pm_tsb_obj, 0, VM_ALLOC_NORMAL |
	    VM_ALLOC_NOBUSY | VM_ALLOC_WIRED | VM_ALLOC_ZERO, ma, TSB_PAGES);
	VM_OBJECT_WUNLOCK(pm->pm_tsb_obj);
	for (i = 0; i < TSB_PAGES; i++)
		ma[i]->md.pmap = pm;
	pmap_qenter((vm_offset_t)pm->pm_tsb, ma, TSB_PAGES);

	bzero(&pm->pm_stats, sizeof(pm->pm_stats));
	return (1);
}