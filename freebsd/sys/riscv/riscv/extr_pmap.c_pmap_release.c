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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_5__ {scalar_t__ resident_count; } ;
struct TYPE_6__ {scalar_t__ pm_l1; int /*<<< orphan*/  pm_active; TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMAP_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allpmaps_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_list ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 

void
pmap_release(pmap_t pmap)
{
	vm_page_t m;

	KASSERT(pmap->pm_stats.resident_count == 0,
	    ("pmap_release: pmap resident count %ld != 0",
	    pmap->pm_stats.resident_count));
	KASSERT(CPU_EMPTY(&pmap->pm_active),
	    ("releasing active pmap %p", pmap));

	mtx_lock(&allpmaps_lock);
	LIST_REMOVE(pmap, pm_list);
	mtx_unlock(&allpmaps_lock);

	m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)pmap->pm_l1));
	vm_page_unwire_noq(m);
	vm_page_free(m);
}