#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct spglist {int dummy; } ;
typedef  TYPE_3__* pmap_t ;
struct TYPE_8__ {int /*<<< orphan*/  resident_count; } ;
struct TYPE_10__ {TYPE_1__ pm_stats; scalar_t__* pm_pdir; } ;
struct TYPE_9__ {size_t pindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* kernel_pmap ; 
 int /*<<< orphan*/  pmap_add_delayed_free_list (TYPE_2__*,struct spglist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_pmap_unwire_ptp(pmap_t pmap, vm_page_t m, struct spglist *free)
{

	/*
	 * unmap the page table page
	 */
	pmap->pm_pdir[m->pindex] = 0;
	--pmap->pm_stats.resident_count;

	/*
	 * There is not need to invalidate the recursive mapping since
	 * we never instantiate such mapping for the usermode pmaps,
	 * and never remove page table pages from the kernel pmap.
	 * Put page on a list so that it is released since all TLB
	 * shootdown is done.
	 */
	MPASS(pmap != kernel_pmap);
	pmap_add_delayed_free_list(m, free, TRUE);
}