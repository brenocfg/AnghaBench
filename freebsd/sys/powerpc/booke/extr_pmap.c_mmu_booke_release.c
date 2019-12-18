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
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_4__ {scalar_t__ resident_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  pm_pdir; int /*<<< orphan*/  pm_pp2d; TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ptbl_root_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmu_booke_release(mmu_t mmu, pmap_t pmap)
{

	KASSERT(pmap->pm_stats.resident_count == 0,
	    ("pmap_release: pmap resident count %ld != 0",
	    pmap->pm_stats.resident_count));
#ifdef __powerpc64__
	uma_zfree(ptbl_root_zone, pmap->pm_pp2d);
#else
	uma_zfree(ptbl_root_zone, pmap->pm_pdir);
#endif
}