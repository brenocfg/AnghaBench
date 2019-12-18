#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int vm_paddr_t ;
typedef  size_t u_int ;
typedef  TYPE_3__* pmap_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_11__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_13__ {scalar_t__* pm_pdir; TYPE_1__ pm_stats; } ;
struct TYPE_12__ {int flags; } ;

/* Variables and functions */
 int PG_A ; 
 int PG_M ; 
 int PG_RW ; 
 int PG_U ; 
 int PG_V ; 
 int PG_ZERO ; 
 size_t PMAP_ENTER_NOSLEEP ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_3__*) ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_2__*) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* vm_page_alloc (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
_pmap_allocpte(pmap_t pmap, u_int ptepindex, u_int flags)
{
	vm_paddr_t ptepa;
	vm_page_t m;

	/*
	 * Allocate a page table page.
	 */
	if ((m = vm_page_alloc(NULL, ptepindex, VM_ALLOC_NOOBJ |
	    VM_ALLOC_WIRED | VM_ALLOC_ZERO)) == NULL) {
		if ((flags & PMAP_ENTER_NOSLEEP) == 0) {
			PMAP_UNLOCK(pmap);
			rw_wunlock(&pvh_global_lock);
			vm_wait(NULL);
			rw_wlock(&pvh_global_lock);
			PMAP_LOCK(pmap);
		}

		/*
		 * Indicate the need to retry.  While waiting, the page table
		 * page may have been allocated.
		 */
		return (NULL);
	}
	if ((m->flags & PG_ZERO) == 0)
		pmap_zero_page(m);

	/*
	 * Map the pagetable page into the process address space, if
	 * it isn't already there.
	 */

	pmap->pm_stats.resident_count++;

	ptepa = VM_PAGE_TO_PHYS(m);
	pmap->pm_pdir[ptepindex] =
		(pd_entry_t) (ptepa | PG_U | PG_RW | PG_V | PG_A | PG_M);

	return (m);
}