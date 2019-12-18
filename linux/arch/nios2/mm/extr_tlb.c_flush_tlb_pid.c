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
struct TYPE_2__ {unsigned int tlb_num_lines; unsigned int tlb_num_ways; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_PTEADDR ; 
 int /*<<< orphan*/  CTL_TLBACC ; 
 int /*<<< orphan*/  CTL_TLBMISC ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long RDCTL (int /*<<< orphan*/ ) ; 
 unsigned long TLBMISC_PID_MASK ; 
 unsigned long TLBMISC_PID_SHIFT ; 
 unsigned int TLBMISC_RD ; 
 unsigned int TLBMISC_WAY_SHIFT ; 
 unsigned int TLBMISC_WE ; 
 int /*<<< orphan*/  WRCTL (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  get_misc_and_pid (unsigned long*,unsigned long*) ; 
 unsigned long pteaddr_invalid (unsigned long) ; 

void flush_tlb_pid(unsigned long mmu_pid)
{
	unsigned long addr = 0;
	unsigned int line;
	unsigned int way;
	unsigned long org_misc, pid_misc;

	/* remember pid/way until we return */
	get_misc_and_pid(&org_misc, &pid_misc);

	for (line = 0; line < cpuinfo.tlb_num_lines; line++) {
		WRCTL(CTL_PTEADDR, pteaddr_invalid(addr));

		for (way = 0; way < cpuinfo.tlb_num_ways; way++) {
			unsigned long tlbmisc;
			unsigned long pid;

			tlbmisc = TLBMISC_RD | (way << TLBMISC_WAY_SHIFT);
			WRCTL(CTL_TLBMISC, tlbmisc);
			tlbmisc = RDCTL(CTL_TLBMISC);
			pid = (tlbmisc >> TLBMISC_PID_SHIFT) & TLBMISC_PID_MASK;
			if (pid != mmu_pid)
				continue;

			tlbmisc = TLBMISC_WE | (way << TLBMISC_WAY_SHIFT);
			WRCTL(CTL_TLBMISC, tlbmisc);
			WRCTL(CTL_TLBACC, 0);
		}

		addr += PAGE_SIZE;
	}

	WRCTL(CTL_TLBMISC, org_misc);
}