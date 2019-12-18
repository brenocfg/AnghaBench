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
typedef  scalar_t__ vm_offset_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DIVCLK_CTRL0 ; 
 int /*<<< orphan*/  CPU_DIVCLK_CTRL2_RATIO_FULL0 ; 
 int /*<<< orphan*/  CPU_DIVCLK_CTRL2_RATIO_FULL1 ; 
 int CPU_DIVCLK_MASK (int) ; 
 int CPU_ID_CPU_MASK ; 
 int CPU_ID_MV88SV584X_V7 ; 
 scalar_t__ CPU_PMU (int) ; 
 scalar_t__ CPU_PMU_BOOT ; 
 scalar_t__ CPU_RESUME_CONTROL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ MP ; 
 scalar_t__ MP_SW_RESET (int) ; 
 scalar_t__ MV_BASE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  armadaxp_init_coher_fabric () ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int cp15_midr_get () ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 scalar_t__ fdt_immr_pa ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int mp_ncpus ; 
 scalar_t__ mpentry ; 
 scalar_t__ mptramp ; 
 scalar_t__ mptramp_end ; 
 scalar_t__ mptramp_pmu_boot ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 int* pmap_mapdev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unmapdev (scalar_t__,int /*<<< orphan*/ ) ; 
 int read_cpu_clkdiv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  write_cpu_clkdiv (int /*<<< orphan*/ ,int) ; 

void
mv_axp_platform_mp_start_ap(platform_t plat)
{
	uint32_t reg, *src, *dst, cpu_num, div_val, cputype;
	vm_offset_t pmu_boot_off;
	/*
	 * Initialization procedure depends on core revision,
	 * in this step CHIP ID is checked to choose proper procedure
	 */
	cputype = cp15_midr_get();
	cputype &= CPU_ID_CPU_MASK;

	/*
	 * Set the PA of CPU0 Boot Address Redirect register used in
	 * mptramp according to the actual SoC registers' base address.
	 */
	pmu_boot_off = (CPU_PMU(0) - MV_BASE) + CPU_PMU_BOOT;
	mptramp_pmu_boot = fdt_immr_pa + pmu_boot_off;
	dst = pmap_mapdev(0xffff0000, PAGE_SIZE);
	for (src = (uint32_t *)mptramp; src < (uint32_t *)mptramp_end;
	    src++, dst++) {
		*dst = *src;
	}
	pmap_unmapdev((vm_offset_t)dst, PAGE_SIZE);
	if (cputype == CPU_ID_MV88SV584X_V7) {
		/* Core rev A0 */
		div_val = read_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1);
		div_val &= 0x3f;

		for (cpu_num = 1; cpu_num < mp_ncpus; cpu_num++ ) {
			reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1);
			reg &= CPU_DIVCLK_MASK(cpu_num);
			reg |= div_val << (cpu_num * 8);
			write_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1, reg);
		}
	} else {
		/* Core rev Z1 */
		div_val = 0x01;

		if (mp_ncpus > 1) {
			reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL0);
			reg &= CPU_DIVCLK_MASK(3);
			reg |= div_val << 24;
			write_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL0, reg);
		}

		for (cpu_num = 2; cpu_num < mp_ncpus; cpu_num++ ) {
			reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1);
			reg &= CPU_DIVCLK_MASK(cpu_num);
			reg |= div_val << (cpu_num * 8);
			write_cpu_clkdiv(CPU_DIVCLK_CTRL2_RATIO_FULL1, reg);
		}
	}

	reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL0);
	reg |= ((0x1 << (mp_ncpus - 1)) - 1) << 21;
	write_cpu_clkdiv(CPU_DIVCLK_CTRL0, reg);
	reg = read_cpu_clkdiv(CPU_DIVCLK_CTRL0);
	reg |= 0x01000000;
	write_cpu_clkdiv(CPU_DIVCLK_CTRL0, reg);

	DELAY(100);
	reg &= ~(0xf << 21);
	write_cpu_clkdiv(CPU_DIVCLK_CTRL0, reg);
	DELAY(100);

	bus_space_write_4(fdtbus_bs_tag, MV_BASE, CPU_RESUME_CONTROL, 0);

	for (cpu_num = 1; cpu_num < mp_ncpus; cpu_num++ )
		bus_space_write_4(fdtbus_bs_tag, CPU_PMU(cpu_num), CPU_PMU_BOOT,
		    pmap_kextract((vm_offset_t)mpentry));

	dcache_wbinv_poc_all();

	for (cpu_num = 1; cpu_num < mp_ncpus; cpu_num++ )
		bus_space_write_4(fdtbus_bs_tag, MP, MP_SW_RESET(cpu_num), 0);

	/* XXX: Temporary workaround for hangup after releasing AP's */
	wmb();
	DELAY(10);

	armadaxp_init_coher_fabric();
}