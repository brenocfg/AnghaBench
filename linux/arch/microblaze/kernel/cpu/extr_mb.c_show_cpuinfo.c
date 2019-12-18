#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_6__ {scalar_t__ k; int /*<<< orphan*/ * s; } ;
struct TYPE_5__ {scalar_t__ fpga_family_code; scalar_t__ ver_code; int cpu_clock_freq; int use_instr; char* mmu; int use_mult; int use_fpu; int use_exc; int icache_size; int dcache_size; int /*<<< orphan*/  pvr_user2; int /*<<< orphan*/  pvr_user1; scalar_t__ hw_debug; scalar_t__ dcache_wb; int /*<<< orphan*/  dcache_line_length; scalar_t__ use_dcache; int /*<<< orphan*/  icache_line_length; scalar_t__ use_icache; scalar_t__ mmu_privins; scalar_t__ endian; } ;
struct TYPE_4__ {scalar_t__ k; int /*<<< orphan*/ * s; } ;

/* Variables and functions */
 int HZ ; 
 char* PAGE_SIZE ; 
 int PVR0_USE_BARREL_MASK ; 
 int PVR0_USE_DIV_MASK ; 
 int PVR0_USE_FPU_MASK ; 
 int PVR0_USE_HW_MUL_MASK ; 
 int PVR2_DIV_ZERO_EXC_MASK ; 
 int PVR2_DOPB_BUS_EXC_MASK ; 
 int PVR2_FPU_EXC_MASK ; 
 int PVR2_ILL_OPCODE_EXC_MASK ; 
 int PVR2_IOPB_BUS_EXC_MASK ; 
 int PVR2_OPCODE_0x0_ILL_MASK ; 
 int PVR2_UNALIGNED_EXC_MASK ; 
 int PVR2_USE_FPU2_MASK ; 
 int PVR2_USE_FSL_EXC ; 
 int PVR2_USE_MSR_INSTR ; 
 int PVR2_USE_MUL64_MASK ; 
 int PVR2_USE_PCMP_INSTR ; 
 TYPE_3__* cpu_ver_lookup ; 
 TYPE_2__ cpuinfo ; 
 TYPE_1__* family_string_lookup ; 
 int loops_per_jiffy ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int show_cpuinfo(struct seq_file *m, void *v)
{
	char *fpga_family = "Unknown";
	char *cpu_ver = "Unknown";
	int i;

	/* Denormalised to get the fpga family string */
	for (i = 0; family_string_lookup[i].s != NULL; i++) {
		if (cpuinfo.fpga_family_code == family_string_lookup[i].k) {
			fpga_family = (char *)family_string_lookup[i].s;
			break;
		}
	}

	/* Denormalised to get the hw version string */
	for (i = 0; cpu_ver_lookup[i].s != NULL; i++) {
		if (cpuinfo.ver_code == cpu_ver_lookup[i].k) {
			cpu_ver = (char *)cpu_ver_lookup[i].s;
			break;
		}
	}

	seq_printf(m,
		   "CPU-Family:	MicroBlaze\n"
		   "FPGA-Arch:	%s\n"
		   "CPU-Ver:	%s, %s endian\n"
		   "CPU-MHz:	%d.%02d\n"
		   "BogoMips:	%lu.%02lu\n",
		   fpga_family,
		   cpu_ver,
		   cpuinfo.endian ? "little" : "big",
		   cpuinfo.cpu_clock_freq / 1000000,
		   cpuinfo.cpu_clock_freq % 1000000,
		   loops_per_jiffy / (500000 / HZ),
		   (loops_per_jiffy / (5000 / HZ)) % 100);

	seq_printf(m,
		   "HW:\n Shift:\t\t%s\n"
		   " MSR:\t\t%s\n"
		   " PCMP:\t\t%s\n"
		   " DIV:\t\t%s\n",
		   (cpuinfo.use_instr & PVR0_USE_BARREL_MASK) ? "yes" : "no",
		   (cpuinfo.use_instr & PVR2_USE_MSR_INSTR) ? "yes" : "no",
		   (cpuinfo.use_instr & PVR2_USE_PCMP_INSTR) ? "yes" : "no",
		   (cpuinfo.use_instr & PVR0_USE_DIV_MASK) ? "yes" : "no");

	seq_printf(m, " MMU:\t\t%x\n", cpuinfo.mmu);

	seq_printf(m,
		   " MUL:\t\t%s\n"
		   " FPU:\t\t%s\n",
		   (cpuinfo.use_mult & PVR2_USE_MUL64_MASK) ? "v2" :
		   (cpuinfo.use_mult & PVR0_USE_HW_MUL_MASK) ? "v1" : "no",
		   (cpuinfo.use_fpu & PVR2_USE_FPU2_MASK) ? "v2" :
		   (cpuinfo.use_fpu & PVR0_USE_FPU_MASK) ? "v1" : "no");

	seq_printf(m,
		   " Exc:\t\t%s%s%s%s%s%s%s%s\n",
		   (cpuinfo.use_exc & PVR2_OPCODE_0x0_ILL_MASK) ? "op0x0 " : "",
		   (cpuinfo.use_exc & PVR2_UNALIGNED_EXC_MASK) ? "unal " : "",
		   (cpuinfo.use_exc & PVR2_ILL_OPCODE_EXC_MASK) ? "ill " : "",
		   (cpuinfo.use_exc & PVR2_IOPB_BUS_EXC_MASK) ? "iopb " : "",
		   (cpuinfo.use_exc & PVR2_DOPB_BUS_EXC_MASK) ? "dopb " : "",
		   (cpuinfo.use_exc & PVR2_DIV_ZERO_EXC_MASK) ? "zero " : "",
		   (cpuinfo.use_exc & PVR2_FPU_EXC_MASK) ? "fpu " : "",
		   (cpuinfo.use_exc & PVR2_USE_FSL_EXC) ? "fsl " : "");

	seq_printf(m,
		   "Stream-insns:\t%sprivileged\n",
		   cpuinfo.mmu_privins ? "un" : "");

	if (cpuinfo.use_icache)
		seq_printf(m,
			   "Icache:\t\t%ukB\tline length:\t%dB\n",
			   cpuinfo.icache_size >> 10,
			   cpuinfo.icache_line_length);
	else
		seq_puts(m, "Icache:\t\tno\n");

	if (cpuinfo.use_dcache) {
		seq_printf(m,
			   "Dcache:\t\t%ukB\tline length:\t%dB\n",
			   cpuinfo.dcache_size >> 10,
			   cpuinfo.dcache_line_length);
		seq_puts(m, "Dcache-Policy:\t");
		if (cpuinfo.dcache_wb)
			seq_puts(m, "write-back\n");
		else
			seq_puts(m, "write-through\n");
	} else {
		seq_puts(m, "Dcache:\t\tno\n");
	}

	seq_printf(m,
		   "HW-Debug:\t%s\n",
		   cpuinfo.hw_debug ? "yes" : "no");

	seq_printf(m,
		   "PVR-USR1:\t%02x\n"
		   "PVR-USR2:\t%08x\n",
		   cpuinfo.pvr_user1,
		   cpuinfo.pvr_user2);

	seq_printf(m, "Page size:\t%lu\n", PAGE_SIZE);

	return 0;
}