#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SUN3_INVALID_PMEG ; 
 unsigned long SUN3_PMEG_MASK ; 
 int /*<<< orphan*/  do_page_mapin (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_emu_map_pmeg (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sun3_get_context () ; 
 scalar_t__ sun3_get_segmap (unsigned long) ; 

__attribute__((used)) static inline void do_pmeg_mapin(unsigned long phys, unsigned long virt,
				 unsigned long type, int pages)
{

	if(sun3_get_segmap(virt & ~SUN3_PMEG_MASK) == SUN3_INVALID_PMEG)
		mmu_emu_map_pmeg(sun3_get_context(), virt);

	while(pages) {
		do_page_mapin(phys, virt, type);
		phys += PAGE_SIZE;
		virt += PAGE_SIZE;
		pages--;
	}
}