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
typedef  int u_int ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  CCR3 ; 
 int CCR3_MAPEN0 ; 
 int /*<<< orphan*/  CCR4 ; 
 int CCR4_CPUID ; 
 int CPUID2_MON ; 
 int CPUID5_MON_MAX_SIZE ; 
 int CPUID5_MON_MIN_SIZE ; 
 int CPUID_PAE ; 
 scalar_t__ CPU_486 ; 
 scalar_t__ CPU_486DLC ; 
 scalar_t__ CPU_BLUE ; 
 scalar_t__ CPU_CY486DX ; 
 scalar_t__ CPU_M1 ; 
 scalar_t__ CPU_M1SC ; 
 scalar_t__ CPU_M2 ; 
 scalar_t__ CPU_VENDOR_AMD ; 
 scalar_t__ CPU_VENDOR_CENTAUR ; 
 scalar_t__ CPU_VENDOR_CYRIX ; 
 scalar_t__ CPU_VENDOR_IBM ; 
 scalar_t__ CPU_VENDOR_INTEL ; 
 scalar_t__ CPU_VENDOR_NSC ; 
 scalar_t__ CPU_VENDOR_TRANSMETA ; 
 scalar_t__ IDENTBLUE_IBMCPU ; 
 int amd_extended_feature_extensions ; 
 int amd_feature ; 
 int amd_feature2 ; 
 int amd_pminfo ; 
 int amd_rascap ; 
 scalar_t__ cpu ; 
 int cpu_exthigh ; 
 int cpu_feature ; 
 int cpu_feature2 ; 
 int cpu_high ; 
 int cpu_id ; 
 int cpu_maxphyaddr ; 
 int cpu_mon_max_size ; 
 int cpu_mon_min_size ; 
 int cpu_mon_mwait_flags ; 
 int cpu_procinfo2 ; 
 char* cpu_vendor ; 
 scalar_t__ cpu_vendor_id ; 
 int cyrix_did ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 scalar_t__ identblue () ; 
 int /*<<< orphan*/  identify_cpu2 () ; 
 int /*<<< orphan*/  identify_cpu_fixup_bsp () ; 
 int /*<<< orphan*/  identifycyrix () ; 
 int read_cyrix_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  write_cyrix_reg (int /*<<< orphan*/ ,int) ; 

void
finishidentcpu(void)
{
	u_int regs[4];
#ifdef __i386__
	u_char ccr3;
#endif

	identify_cpu_fixup_bsp();

	if (cpu_high >= 5 && (cpu_feature2 & CPUID2_MON) != 0) {
		do_cpuid(5, regs);
		cpu_mon_mwait_flags = regs[2];
		cpu_mon_min_size = regs[0] &  CPUID5_MON_MIN_SIZE;
		cpu_mon_max_size = regs[1] &  CPUID5_MON_MAX_SIZE;
	}

	identify_cpu2();

#ifdef __i386__
	if (cpu_high > 0 &&
	    (cpu_vendor_id == CPU_VENDOR_INTEL ||
	     cpu_vendor_id == CPU_VENDOR_AMD ||
	     cpu_vendor_id == CPU_VENDOR_TRANSMETA ||
	     cpu_vendor_id == CPU_VENDOR_CENTAUR ||
	     cpu_vendor_id == CPU_VENDOR_NSC)) {
		do_cpuid(0x80000000, regs);
		if (regs[0] >= 0x80000000)
			cpu_exthigh = regs[0];
	}
#else
	if (cpu_vendor_id == CPU_VENDOR_INTEL ||
	    cpu_vendor_id == CPU_VENDOR_AMD ||
	    cpu_vendor_id == CPU_VENDOR_CENTAUR) {
		do_cpuid(0x80000000, regs);
		cpu_exthigh = regs[0];
	}
#endif
	if (cpu_exthigh >= 0x80000001) {
		do_cpuid(0x80000001, regs);
		amd_feature = regs[3] & ~(cpu_feature & 0x0183f3ff);
		amd_feature2 = regs[2];
	}
	if (cpu_exthigh >= 0x80000007) {
		do_cpuid(0x80000007, regs);
		amd_rascap = regs[1];
		amd_pminfo = regs[3];
	}
	if (cpu_exthigh >= 0x80000008) {
		do_cpuid(0x80000008, regs);
		cpu_maxphyaddr = regs[0] & 0xff;
		amd_extended_feature_extensions = regs[1];
		cpu_procinfo2 = regs[2];
	} else {
		cpu_maxphyaddr = (cpu_feature & CPUID_PAE) != 0 ? 36 : 32;
	}

#ifdef __i386__
	if (cpu_vendor_id == CPU_VENDOR_CYRIX) {
		if (cpu == CPU_486) {
			/*
			 * These conditions are equivalent to:
			 *     - CPU does not support cpuid instruction.
			 *     - Cyrix/IBM CPU is detected.
			 */
			if (identblue() == IDENTBLUE_IBMCPU) {
				strcpy(cpu_vendor, "IBM");
				cpu_vendor_id = CPU_VENDOR_IBM;
				cpu = CPU_BLUE;
				return;
			}
		}
		switch (cpu_id & 0xf00) {
		case 0x600:
			/*
			 * Cyrix's datasheet does not describe DIRs.
			 * Therefor, I assume it does not have them
			 * and use the result of the cpuid instruction.
			 * XXX they seem to have it for now at least. -Peter
			 */
			identifycyrix();
			cpu = CPU_M2;
			break;
		default:
			identifycyrix();
			/*
			 * This routine contains a trick.
			 * Don't check (cpu_id & 0x00f0) == 0x50 to detect M2, now.
			 */
			switch (cyrix_did & 0x00f0) {
			case 0x00:
			case 0xf0:
				cpu = CPU_486DLC;
				break;
			case 0x10:
				cpu = CPU_CY486DX;
				break;
			case 0x20:
				if ((cyrix_did & 0x000f) < 8)
					cpu = CPU_M1;
				else
					cpu = CPU_M1SC;
				break;
			case 0x30:
				cpu = CPU_M1;
				break;
			case 0x40:
				/* MediaGX CPU */
				cpu = CPU_M1SC;
				break;
			default:
				/* M2 and later CPUs are treated as M2. */
				cpu = CPU_M2;

				/*
				 * enable cpuid instruction.
				 */
				ccr3 = read_cyrix_reg(CCR3);
				write_cyrix_reg(CCR3, CCR3_MAPEN0);
				write_cyrix_reg(CCR4, read_cyrix_reg(CCR4) | CCR4_CPUID);
				write_cyrix_reg(CCR3, ccr3);

				do_cpuid(0, regs);
				cpu_high = regs[0];	/* eax */
				do_cpuid(1, regs);
				cpu_id = regs[0];	/* eax */
				cpu_feature = regs[3];	/* edx */
				break;
			}
		}
	} else if (cpu == CPU_486 && *cpu_vendor == '\0') {
		/*
		 * There are BlueLightning CPUs that do not change
		 * undefined flags by dividing 5 by 2.  In this case,
		 * the CPU identification routine in locore.s leaves
		 * cpu_vendor null string and puts CPU_486 into the
		 * cpu.
		 */
		if (identblue() == IDENTBLUE_IBMCPU) {
			strcpy(cpu_vendor, "IBM");
			cpu_vendor_id = CPU_VENDOR_IBM;
			cpu = CPU_BLUE;
			return;
		}
	}
#endif
}