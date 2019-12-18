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
struct TYPE_2__ {int dcache_line_size; unsigned long dcache_size; } ;

/* Variables and functions */
 TYPE_1__ cpuinfo ; 

__attribute__((used)) static void __flush_dcache(unsigned long start, unsigned long end)
{
	unsigned long addr;

	start &= ~(cpuinfo.dcache_line_size - 1);
	end += (cpuinfo.dcache_line_size - 1);
	end &= ~(cpuinfo.dcache_line_size - 1);

	if (end > start + cpuinfo.dcache_size)
		end = start + cpuinfo.dcache_size;

	for (addr = start; addr < end; addr += cpuinfo.dcache_line_size) {
		__asm__ __volatile__ ("   flushd 0(%0)\n"
					: /* Outputs */
					: /* Inputs  */ "r"(addr)
					/* : No clobber */);
	}
}