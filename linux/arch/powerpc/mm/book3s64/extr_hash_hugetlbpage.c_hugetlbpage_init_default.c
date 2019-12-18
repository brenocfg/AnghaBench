#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ shift; } ;

/* Variables and functions */
 size_t MMU_PAGE_16M ; 
 size_t MMU_PAGE_1M ; 
 size_t MMU_PAGE_2M ; 
 scalar_t__ hpage_shift ; 
 TYPE_1__* mmu_psize_defs ; 

void hugetlbpage_init_default(void)
{
	/* Set default large page size. Currently, we pick 16M or 1M
	 * depending on what is available
	 */
	if (mmu_psize_defs[MMU_PAGE_16M].shift)
		hpage_shift = mmu_psize_defs[MMU_PAGE_16M].shift;
	else if (mmu_psize_defs[MMU_PAGE_1M].shift)
		hpage_shift = mmu_psize_defs[MMU_PAGE_1M].shift;
	else if (mmu_psize_defs[MMU_PAGE_2M].shift)
		hpage_shift = mmu_psize_defs[MMU_PAGE_2M].shift;
}