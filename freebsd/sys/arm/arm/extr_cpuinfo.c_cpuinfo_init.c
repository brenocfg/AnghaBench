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
typedef  int uint32_t ;
struct TYPE_2__ {int midr; int architecture; int revision; int implementer; int part_number; int patch; unsigned int mpidr; int revidr; int id_pfr0; int id_pfr1; int id_mmfr0; int id_mmfr2; int id_mmfr3; int id_isar0; int id_isar5; int outermost_shareability; int shareability_levels; int auxiliary_registers; int innermost_shareability; int mem_barrier; int coherent_walk; int maintenance_broadcast; int generic_timer_ext; int virtualization_ext; int security_ext; unsigned int mp_ext; int dcache_line_size; int icache_line_size; int dcache_line_mask; int icache_line_mask; int /*<<< orphan*/  ctr; int /*<<< orphan*/  clidr; int /*<<< orphan*/  ccsidr; int /*<<< orphan*/  id_isar4; int /*<<< orphan*/  id_isar3; int /*<<< orphan*/  id_isar2; int /*<<< orphan*/  id_isar1; int /*<<< orphan*/  id_mmfr1; int /*<<< orphan*/  id_afr0; int /*<<< orphan*/  id_dfr0; int /*<<< orphan*/  tlbtr; int /*<<< orphan*/  tcmtr; } ;

/* Variables and functions */
 scalar_t__ CPU_CT_ARMV7 ; 
 int CPU_CT_DMINLINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_CT_DSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_CT_FORMAT (int /*<<< orphan*/ ) ; 
 int CPU_CT_IMINLINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_CT_ISIZE (int /*<<< orphan*/ ) ; 
 int CPU_CT_xSIZE_LEN (int /*<<< orphan*/ ) ; 
 int CPU_ID_ARM_LTD ; 
 int CPU_ID_IMPLEMENTOR_MASK ; 
 scalar_t__ CPU_ID_IS7 (int) ; 
 scalar_t__ CPU_ID_ISOLD (int) ; 
 int /*<<< orphan*/  HWCAP2_AES ; 
 int /*<<< orphan*/  HWCAP2_CRC32 ; 
 int /*<<< orphan*/  HWCAP2_PMULL ; 
 int /*<<< orphan*/  HWCAP2_SHA1 ; 
 int /*<<< orphan*/  HWCAP2_SHA2 ; 
 int HWCAP_EDSP ; 
 int HWCAP_FAST_MULT ; 
 int HWCAP_HALF ; 
 int HWCAP_IDIVA ; 
 int HWCAP_IDIVT ; 
 int HWCAP_LPAE ; 
 int HWCAP_THUMB ; 
 int HWCAP_THUMBEE ; 
 int HWCAP_TLS ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp15_ccsidr_get () ; 
 int /*<<< orphan*/  cp15_clidr_get () ; 
 int /*<<< orphan*/  cp15_ctr_get () ; 
 int /*<<< orphan*/  cp15_id_afr0_get () ; 
 int /*<<< orphan*/  cp15_id_dfr0_get () ; 
 int cp15_id_isar0_get () ; 
 int /*<<< orphan*/  cp15_id_isar1_get () ; 
 int /*<<< orphan*/  cp15_id_isar2_get () ; 
 int /*<<< orphan*/  cp15_id_isar3_get () ; 
 int /*<<< orphan*/  cp15_id_isar4_get () ; 
 int cp15_id_isar5_get () ; 
 int cp15_id_mmfr0_get () ; 
 int /*<<< orphan*/  cp15_id_mmfr1_get () ; 
 int cp15_id_mmfr2_get () ; 
 int cp15_id_mmfr3_get () ; 
 int cp15_id_pfr0_get () ; 
 int cp15_id_pfr1_get () ; 
 int cp15_midr_get () ; 
 unsigned int cp15_mpidr_get () ; 
 int cp15_revidr_get () ; 
 int /*<<< orphan*/  cp15_tcmtr_get () ; 
 int /*<<< orphan*/  cp15_tlbtr_get () ; 
 int /*<<< orphan*/  cpu_quirks_actlr_mask ; 
 int /*<<< orphan*/  cpu_quirks_actlr_set ; 
 TYPE_1__ cpuinfo ; 
 int elf_hwcap ; 
 int /*<<< orphan*/  elf_hwcap2 ; 

void
cpuinfo_init(void)
{
#if __ARM_ARCH >= 6
	uint32_t tmp;
#endif

	/*
	 * Prematurely fetch CPU quirks. Standard fetch for tunable
	 * sysctls is handled using SYSINIT, thus too late for boot CPU.
	 * Keep names in sync with sysctls.
	 */
	TUNABLE_INT_FETCH("hw.cpu.quirks.actlr_mask", &cpu_quirks_actlr_mask);
	TUNABLE_INT_FETCH("hw.cpu.quirks.actlr_set", &cpu_quirks_actlr_set);

	cpuinfo.midr = cp15_midr_get();
	/* Test old version id schemes first */
	if ((cpuinfo.midr & CPU_ID_IMPLEMENTOR_MASK) == CPU_ID_ARM_LTD) {
		if (CPU_ID_ISOLD(cpuinfo.midr)) {
			/* obsolete ARMv2 or ARMv3 CPU */
			cpuinfo.midr = 0;
			return;
		}
		if (CPU_ID_IS7(cpuinfo.midr)) {
			if ((cpuinfo.midr & (1 << 23)) == 0) {
				/* obsolete ARMv3 CPU */
				cpuinfo.midr = 0;
				return;
			}
			/* ARMv4T CPU */
			cpuinfo.architecture = 1;
			cpuinfo.revision = (cpuinfo.midr >> 16) & 0x7F;
		} else {
			/* ARM new id scheme */
			cpuinfo.architecture = (cpuinfo.midr >> 16) & 0x0F;
			cpuinfo.revision = (cpuinfo.midr >> 20) & 0x0F;
		}
	} else {
		/* non ARM -> must be new id scheme */
		cpuinfo.architecture = (cpuinfo.midr >> 16) & 0x0F;
		cpuinfo.revision = (cpuinfo.midr >> 20) & 0x0F;
	}
	/* Parse rest of MIDR  */
	cpuinfo.implementer = (cpuinfo.midr >> 24) & 0xFF;
	cpuinfo.part_number = (cpuinfo.midr >> 4) & 0xFFF;
	cpuinfo.patch = cpuinfo.midr & 0x0F;

	/* CP15 c0,c0 regs 0-7 exist on all CPUs (although aliased with MIDR) */
	cpuinfo.ctr = cp15_ctr_get();
	cpuinfo.tcmtr = cp15_tcmtr_get();
#if __ARM_ARCH >= 6
	cpuinfo.tlbtr = cp15_tlbtr_get();
	cpuinfo.mpidr = cp15_mpidr_get();
	cpuinfo.revidr = cp15_revidr_get();
#endif

	/* if CPU is not v7 cpu id scheme */
	if (cpuinfo.architecture != 0xF)
		return;
#if __ARM_ARCH >= 6
	cpuinfo.id_pfr0 = cp15_id_pfr0_get();
	cpuinfo.id_pfr1 = cp15_id_pfr1_get();
	cpuinfo.id_dfr0 = cp15_id_dfr0_get();
	cpuinfo.id_afr0 = cp15_id_afr0_get();
	cpuinfo.id_mmfr0 = cp15_id_mmfr0_get();
	cpuinfo.id_mmfr1 = cp15_id_mmfr1_get();
	cpuinfo.id_mmfr2 = cp15_id_mmfr2_get();
	cpuinfo.id_mmfr3 = cp15_id_mmfr3_get();
	cpuinfo.id_isar0 = cp15_id_isar0_get();
	cpuinfo.id_isar1 = cp15_id_isar1_get();
	cpuinfo.id_isar2 = cp15_id_isar2_get();
	cpuinfo.id_isar3 = cp15_id_isar3_get();
	cpuinfo.id_isar4 = cp15_id_isar4_get();
	cpuinfo.id_isar5 = cp15_id_isar5_get();

/* Not yet - CBAR only exist on ARM SMP Cortex A CPUs
	cpuinfo.cbar = cp15_cbar_get();
*/
	if (CPU_CT_FORMAT(cpuinfo.ctr) == CPU_CT_ARMV7) {
		cpuinfo.ccsidr = cp15_ccsidr_get();
		cpuinfo.clidr = cp15_clidr_get();
	}

	/* Test if revidr is implemented */
	if (cpuinfo.revidr == cpuinfo.midr)
		cpuinfo.revidr = 0;

	/* parsed bits of above registers */
	/* id_mmfr0 */
	cpuinfo.outermost_shareability =  (cpuinfo.id_mmfr0 >> 8) & 0xF;
	cpuinfo.shareability_levels = (cpuinfo.id_mmfr0 >> 12) & 0xF;
	cpuinfo.auxiliary_registers = (cpuinfo.id_mmfr0 >> 20) & 0xF;
	cpuinfo.innermost_shareability = (cpuinfo.id_mmfr0 >> 28) & 0xF;
	/* id_mmfr2 */
	cpuinfo.mem_barrier = (cpuinfo.id_mmfr2 >> 20) & 0xF;
	/* id_mmfr3 */
	cpuinfo.coherent_walk = (cpuinfo.id_mmfr3 >> 20) & 0xF;
	cpuinfo.maintenance_broadcast =(cpuinfo.id_mmfr3 >> 12) & 0xF;
	/* id_pfr1 */
	cpuinfo.generic_timer_ext = (cpuinfo.id_pfr1 >> 16) & 0xF;
	cpuinfo.virtualization_ext = (cpuinfo.id_pfr1 >> 12) & 0xF;
	cpuinfo.security_ext = (cpuinfo.id_pfr1 >> 4) & 0xF;
	/* mpidr */
	cpuinfo.mp_ext = (cpuinfo.mpidr >> 31u) & 0x1;

	/* L1 Cache sizes */
	if (CPU_CT_FORMAT(cpuinfo.ctr) == CPU_CT_ARMV7) {
		cpuinfo.dcache_line_size =
		    1 << (CPU_CT_DMINLINE(cpuinfo.ctr) + 2);
		cpuinfo.icache_line_size =
		    1 << (CPU_CT_IMINLINE(cpuinfo.ctr) + 2);
	} else {
		cpuinfo.dcache_line_size =
		    1 << (CPU_CT_xSIZE_LEN(CPU_CT_DSIZE(cpuinfo.ctr)) + 3);
		cpuinfo.icache_line_size =
		    1 << (CPU_CT_xSIZE_LEN(CPU_CT_ISIZE(cpuinfo.ctr)) + 3);
	}
	cpuinfo.dcache_line_mask = cpuinfo.dcache_line_size - 1;
	cpuinfo.icache_line_mask = cpuinfo.icache_line_size - 1;

	/* Fill AT_HWCAP bits. */
	elf_hwcap |= HWCAP_HALF | HWCAP_FAST_MULT; /* Required for all CPUs */
	elf_hwcap |= HWCAP_TLS | HWCAP_EDSP;	   /* Required for v6+ CPUs */

	tmp = (cpuinfo.id_isar0 >> 24) & 0xF;	/* Divide_instrs */
	if (tmp >= 1)
		elf_hwcap |= HWCAP_IDIVT;
	if (tmp >= 2)
		elf_hwcap |= HWCAP_IDIVA;

	tmp = (cpuinfo.id_pfr0 >> 4) & 0xF; 	/* State1  */
	if (tmp >= 1)
		elf_hwcap |= HWCAP_THUMB;

	tmp = (cpuinfo.id_pfr0 >> 12) & 0xF; 	/* State3  */
	if (tmp >= 1)
		elf_hwcap |= HWCAP_THUMBEE;

	tmp = (cpuinfo.id_mmfr0 >> 0) & 0xF; 	/* VMSA */
	if (tmp >= 5)
		elf_hwcap |= HWCAP_LPAE;

	/* Fill AT_HWCAP2 bits. */
	tmp = (cpuinfo.id_isar5 >> 4) & 0xF;	/* AES */
	if (tmp >= 1)
		elf_hwcap2 |= HWCAP2_AES;
	if (tmp >= 2)
		elf_hwcap2 |= HWCAP2_PMULL;

	tmp = (cpuinfo.id_isar5 >> 8) & 0xF;	/* SHA1 */
	if (tmp >= 1)
		elf_hwcap2 |= HWCAP2_SHA1;

	tmp = (cpuinfo.id_isar5 >> 12) & 0xF;	/* SHA2 */
	if (tmp >= 1)
		elf_hwcap2 |= HWCAP2_SHA2;

	tmp = (cpuinfo.id_isar5 >> 16) & 0xF;	/* CRC32 */
	if (tmp >= 1)
		elf_hwcap2 |= HWCAP2_CRC32;
#endif
}