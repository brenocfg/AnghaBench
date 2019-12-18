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
struct cpuinfo_mips {int processor_id; scalar_t__ cputype; int fpu_msk31; int options; int ases; int srsets; int msa_id; int /*<<< orphan*/  fpu_csr31; int /*<<< orphan*/  writecombine; int /*<<< orphan*/  fpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CPU_UNKNOWN ; 
 int /*<<< orphan*/  FPIR_IMP_NONE ; 
 int FPU_CSR_ABS2008 ; 
 int FPU_CSR_NAN2008 ; 
 int /*<<< orphan*/  FPU_CSR_RN ; 
 int FPU_CSR_RSVD ; 
 int /*<<< orphan*/  HWCAP_LOONGSON_EXT ; 
 int /*<<< orphan*/  HWCAP_LOONGSON_EXT2 ; 
 int /*<<< orphan*/  HWCAP_LOONGSON_MMI ; 
 int /*<<< orphan*/  HWCAP_MIPS_DSP ; 
 int /*<<< orphan*/  HWCAP_MIPS_DSP2 ; 
 int /*<<< orphan*/  HWCAP_MIPS_DSP3 ; 
 int /*<<< orphan*/  HWCAP_MIPS_MDMX ; 
 int /*<<< orphan*/  HWCAP_MIPS_MIPS16 ; 
 int /*<<< orphan*/  HWCAP_MIPS_MIPS16E2 ; 
 int /*<<< orphan*/  HWCAP_MIPS_MIPS3D ; 
 int /*<<< orphan*/  HWCAP_MIPS_MSA ; 
 int /*<<< orphan*/  HWCAP_MIPS_R6 ; 
 int /*<<< orphan*/  HWCAP_MIPS_SMARTMIPS ; 
 int MIPS_ASE_DSP ; 
 int MIPS_ASE_DSP2P ; 
 int MIPS_CPU_FPU ; 
 int MIPS_CPU_HTW ; 
 int MIPS_CPU_PCI ; 
 int MIPS_CPU_RIXIEX ; 
 int MIPS_PWCTL_PWEN_SHIFT ; 
 int MSA_IR_WRPF ; 
 int PG_IEC ; 
#define  PRID_COMP_ALCHEMY 140 
#define  PRID_COMP_BROADCOM 139 
#define  PRID_COMP_CAVIUM 138 
#define  PRID_COMP_INGENIC_D0 137 
#define  PRID_COMP_INGENIC_D1 136 
#define  PRID_COMP_INGENIC_E1 135 
#define  PRID_COMP_LEGACY 134 
#define  PRID_COMP_LOONGSON 133 
 int PRID_COMP_MASK ; 
#define  PRID_COMP_MIPS 132 
#define  PRID_COMP_NETLOGIC 131 
#define  PRID_COMP_NXP 130 
#define  PRID_COMP_SANDCRAFT 129 
#define  PRID_COMP_SIBYTE 128 
 int PRID_IMP_UNKNOWN ; 
 int R10K_DIAG_E_GHIST ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  _CACHE_UNCACHED ; 
 int /*<<< orphan*/ * __cpu_name ; 
 unsigned long long __ua_limit ; 
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 int cpu_get_msa_id () ; 
 scalar_t__ cpu_has_bp_ghist ; 
 scalar_t__ cpu_has_dsp ; 
 scalar_t__ cpu_has_dsp2 ; 
 scalar_t__ cpu_has_dsp3 ; 
 scalar_t__ cpu_has_loongson_ext ; 
 scalar_t__ cpu_has_loongson_ext2 ; 
 scalar_t__ cpu_has_loongson_mmi ; 
 scalar_t__ cpu_has_mdmx ; 
 scalar_t__ cpu_has_mips16 ; 
 scalar_t__ cpu_has_mips16e2 ; 
 scalar_t__ cpu_has_mips3d ; 
 scalar_t__ cpu_has_mips_r2_r6 ; 
 scalar_t__ cpu_has_mips_r6 ; 
 scalar_t__ cpu_has_msa ; 
 scalar_t__ cpu_has_rixi ; 
 scalar_t__ cpu_has_smartmips ; 
 scalar_t__ cpu_has_vz ; 
 int /*<<< orphan*/  cpu_probe_alchemy (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_broadcom (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_cavium (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_ingenic (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_legacy (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_loongson (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_mips (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_netlogic (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_nxp (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_sandcraft (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_sibyte (struct cpuinfo_mips*,unsigned int) ; 
 int /*<<< orphan*/  cpu_probe_vmbits (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_probe_vz (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_set_fpu_opts (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_set_nofpu_opts (struct cpuinfo_mips*) ; 
 unsigned long long cpu_vmbits ; 
 struct cpuinfo_mips current_cpu_data ; 
 scalar_t__ current_cpu_type () ; 
 int /*<<< orphan*/  elf_hwcap ; 
 scalar_t__ mips_dsp_disabled ; 
 scalar_t__ mips_fpu_disabled ; 
 scalar_t__ mips_htw_disabled ; 
 int read_c0_pagegrain () ; 
 int read_c0_prid () ; 
 int read_c0_pwctl () ; 
 int read_c0_r10k_diag () ; 
 int read_c0_srsctl () ; 
 int /*<<< orphan*/  set_c0_pagegrain (int) ; 
 int /*<<< orphan*/  set_elf_platform (unsigned int,char*) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  write_c0_pwctl (int) ; 
 int /*<<< orphan*/  write_c0_r10k_diag (int) ; 

void cpu_probe(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;
	unsigned int cpu = smp_processor_id();

	/*
	 * Set a default elf platform, cpu probe may later
	 * overwrite it with a more precise value
	 */
	set_elf_platform(cpu, "mips");

	c->processor_id = PRID_IMP_UNKNOWN;
	c->fpu_id	= FPIR_IMP_NONE;
	c->cputype	= CPU_UNKNOWN;
	c->writecombine = _CACHE_UNCACHED;

	c->fpu_csr31	= FPU_CSR_RN;
	c->fpu_msk31	= FPU_CSR_RSVD | FPU_CSR_ABS2008 | FPU_CSR_NAN2008;

	c->processor_id = read_c0_prid();
	switch (c->processor_id & PRID_COMP_MASK) {
	case PRID_COMP_LEGACY:
		cpu_probe_legacy(c, cpu);
		break;
	case PRID_COMP_MIPS:
		cpu_probe_mips(c, cpu);
		break;
	case PRID_COMP_ALCHEMY:
		cpu_probe_alchemy(c, cpu);
		break;
	case PRID_COMP_SIBYTE:
		cpu_probe_sibyte(c, cpu);
		break;
	case PRID_COMP_BROADCOM:
		cpu_probe_broadcom(c, cpu);
		break;
	case PRID_COMP_SANDCRAFT:
		cpu_probe_sandcraft(c, cpu);
		break;
	case PRID_COMP_NXP:
		cpu_probe_nxp(c, cpu);
		break;
	case PRID_COMP_CAVIUM:
		cpu_probe_cavium(c, cpu);
		break;
	case PRID_COMP_LOONGSON:
		cpu_probe_loongson(c, cpu);
		break;
	case PRID_COMP_INGENIC_D0:
	case PRID_COMP_INGENIC_D1:
	case PRID_COMP_INGENIC_E1:
		cpu_probe_ingenic(c, cpu);
		break;
	case PRID_COMP_NETLOGIC:
		cpu_probe_netlogic(c, cpu);
		break;
	}

	BUG_ON(!__cpu_name[cpu]);
	BUG_ON(c->cputype == CPU_UNKNOWN);

	/*
	 * Platform code can force the cpu type to optimize code
	 * generation. In that case be sure the cpu type is correctly
	 * manually setup otherwise it could trigger some nasty bugs.
	 */
	BUG_ON(current_cpu_type() != c->cputype);

	if (cpu_has_rixi) {
		/* Enable the RIXI exceptions */
		set_c0_pagegrain(PG_IEC);
		back_to_back_c0_hazard();
		/* Verify the IEC bit is set */
		if (read_c0_pagegrain() & PG_IEC)
			c->options |= MIPS_CPU_RIXIEX;
	}

	if (mips_fpu_disabled)
		c->options &= ~MIPS_CPU_FPU;

	if (mips_dsp_disabled)
		c->ases &= ~(MIPS_ASE_DSP | MIPS_ASE_DSP2P);

	if (mips_htw_disabled) {
		c->options &= ~MIPS_CPU_HTW;
		write_c0_pwctl(read_c0_pwctl() &
			       ~(1 << MIPS_PWCTL_PWEN_SHIFT));
	}

	if (c->options & MIPS_CPU_FPU)
		cpu_set_fpu_opts(c);
	else
		cpu_set_nofpu_opts(c);

	if (cpu_has_bp_ghist)
		write_c0_r10k_diag(read_c0_r10k_diag() |
				   R10K_DIAG_E_GHIST);

	if (cpu_has_mips_r2_r6) {
		c->srsets = ((read_c0_srsctl() >> 26) & 0x0f) + 1;
		/* R2 has Performance Counter Interrupt indicator */
		c->options |= MIPS_CPU_PCI;
	}
	else
		c->srsets = 1;

	if (cpu_has_mips_r6)
		elf_hwcap |= HWCAP_MIPS_R6;

	if (cpu_has_msa) {
		c->msa_id = cpu_get_msa_id();
		WARN(c->msa_id & MSA_IR_WRPF,
		     "Vector register partitioning unimplemented!");
		elf_hwcap |= HWCAP_MIPS_MSA;
	}

	if (cpu_has_mips16)
		elf_hwcap |= HWCAP_MIPS_MIPS16;

	if (cpu_has_mdmx)
		elf_hwcap |= HWCAP_MIPS_MDMX;

	if (cpu_has_mips3d)
		elf_hwcap |= HWCAP_MIPS_MIPS3D;

	if (cpu_has_smartmips)
		elf_hwcap |= HWCAP_MIPS_SMARTMIPS;

	if (cpu_has_dsp)
		elf_hwcap |= HWCAP_MIPS_DSP;

	if (cpu_has_dsp2)
		elf_hwcap |= HWCAP_MIPS_DSP2;

	if (cpu_has_dsp3)
		elf_hwcap |= HWCAP_MIPS_DSP3;

	if (cpu_has_mips16e2)
		elf_hwcap |= HWCAP_MIPS_MIPS16E2;

	if (cpu_has_loongson_mmi)
		elf_hwcap |= HWCAP_LOONGSON_MMI;

	if (cpu_has_loongson_ext)
		elf_hwcap |= HWCAP_LOONGSON_EXT;

	if (cpu_has_loongson_ext2)
		elf_hwcap |= HWCAP_LOONGSON_EXT2;

	if (cpu_has_vz)
		cpu_probe_vz(c);

	cpu_probe_vmbits(c);

#ifdef CONFIG_64BIT
	if (cpu == 0)
		__ua_limit = ~((1ull << cpu_vmbits) - 1);
#endif
}