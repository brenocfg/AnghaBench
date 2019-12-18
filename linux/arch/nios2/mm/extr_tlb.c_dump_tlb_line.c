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
struct TYPE_2__ {unsigned long tlb_num_ways_log2; unsigned int tlb_num_ways; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_PTEADDR ; 
 int /*<<< orphan*/  CTL_TLBACC ; 
 int /*<<< orphan*/  CTL_TLBMISC ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long RDCTL (int /*<<< orphan*/ ) ; 
 unsigned long TLBMISC_PID ; 
 unsigned long TLBMISC_PID_MASK ; 
 unsigned long TLBMISC_PID_SHIFT ; 
 unsigned int TLBMISC_RD ; 
 unsigned long TLBMISC_WAY ; 
 unsigned int TLBMISC_WAY_SHIFT ; 
 int /*<<< orphan*/  WRCTL (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long _PAGE_CACHED ; 
 unsigned long _PAGE_EXEC ; 
 unsigned long _PAGE_GLOBAL ; 
 unsigned long _PAGE_READ ; 
 unsigned long _PAGE_WRITE ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned long,...) ; 

void dump_tlb_line(unsigned long line)
{
	unsigned int way;
	unsigned long org_misc;

	pr_debug("dump tlb-entries for line=%#lx (addr %08lx)\n", line,
		line << (PAGE_SHIFT + cpuinfo.tlb_num_ways_log2));

	/* remember pid/way until we return */
	org_misc = (RDCTL(CTL_TLBMISC) & (TLBMISC_PID | TLBMISC_WAY));

	WRCTL(CTL_PTEADDR, line << 2);

	for (way = 0; way < cpuinfo.tlb_num_ways; way++) {
		unsigned long pteaddr;
		unsigned long tlbmisc;
		unsigned long tlbacc;

		WRCTL(CTL_TLBMISC, TLBMISC_RD | (way << TLBMISC_WAY_SHIFT));
		pteaddr = RDCTL(CTL_PTEADDR);
		tlbmisc = RDCTL(CTL_TLBMISC);
		tlbacc = RDCTL(CTL_TLBACC);

		if ((tlbacc << PAGE_SHIFT) != 0) {
			pr_debug("-- way:%02x vpn:0x%08lx phys:0x%08lx pid:0x%02lx flags:%c%c%c%c%c\n",
				way,
				(pteaddr << (PAGE_SHIFT-2)),
				(tlbacc << PAGE_SHIFT),
				((tlbmisc >> TLBMISC_PID_SHIFT) &
				TLBMISC_PID_MASK),
				(tlbacc & _PAGE_READ ? 'r' : '-'),
				(tlbacc & _PAGE_WRITE ? 'w' : '-'),
				(tlbacc & _PAGE_EXEC ? 'x' : '-'),
				(tlbacc & _PAGE_GLOBAL ? 'g' : '-'),
				(tlbacc & _PAGE_CACHED ? 'c' : '-'));
		}
	}

	WRCTL(CTL_TLBMISC, org_misc);
}