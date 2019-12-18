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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  elf_platform ; 
 int loops_per_jiffy ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int uc32_cpuid ; 

__attribute__((used)) static int c_show(struct seq_file *m, void *v)
{
	seq_printf(m, "Processor\t: UniCore-II rev %d (%s)\n",
		   (int)(uc32_cpuid >> 16) & 15, elf_platform);

	seq_printf(m, "BogoMIPS\t: %lu.%02lu\n",
		   loops_per_jiffy / (500000/HZ),
		   (loops_per_jiffy / (5000/HZ)) % 100);

	/* dump out the processor features */
	seq_puts(m, "Features\t: CMOV UC-F64");

	seq_printf(m, "\nCPU implementer\t: 0x%02x\n", uc32_cpuid >> 24);
	seq_printf(m, "CPU architecture: 2\n");
	seq_printf(m, "CPU revision\t: %d\n", (uc32_cpuid >> 16) & 15);

	seq_printf(m, "Cache type\t: write-back\n"
			"Cache clean\t: cp0 c5 ops\n"
			"Cache lockdown\t: not support\n"
			"Cache format\t: Harvard\n");

	seq_puts(m, "\n");

	seq_printf(m, "Hardware\t: PKUnity v3\n");

	return 0;
}