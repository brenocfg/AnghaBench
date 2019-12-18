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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMEM_PHYSBASE ; 
 int /*<<< orphan*/  IMEM_SIZE ; 
 int /*<<< orphan*/  PMU_PHYSBASE ; 
 int /*<<< orphan*/  PMU_PWRDN_CON ; 
 int PMU_PWRDN_SCU ; 
 int /*<<< orphan*/  PMU_SIZE ; 
 int SCU_CONTROL_ENABLE ; 
 int /*<<< orphan*/  SCU_CONTROL_REG ; 
 int /*<<< orphan*/  SCU_INV_TAGS_REG ; 
 int /*<<< orphan*/  SCU_PHYSBASE ; 
 int /*<<< orphan*/  SCU_SIZE ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_region_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int mp_ncpus ; 
 scalar_t__ mpentry ; 
 char* mpentry_addr ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk30xx_boot2 ; 
 int /*<<< orphan*/  sev () ; 

void
rk30xx_mp_start_ap(platform_t plat)
{
	bus_space_handle_t scu;
	bus_space_handle_t imem;
	bus_space_handle_t pmu;
	uint32_t val;
	int i;

	if (bus_space_map(fdtbus_bs_tag, SCU_PHYSBASE, SCU_SIZE, 0, &scu) != 0)
		panic("Could not map the SCU");
	if (bus_space_map(fdtbus_bs_tag, IMEM_PHYSBASE,
	    IMEM_SIZE, 0, &imem) != 0)
		panic("Could not map the IMEM");
	if (bus_space_map(fdtbus_bs_tag, PMU_PHYSBASE, PMU_SIZE, 0, &pmu) != 0)
		panic("Could not map the PMU");

	/*
	 * Invalidate SCU cache tags.  The 0x0000ffff constant invalidates all
	 * ways on all cores 0-3. Per the ARM docs, it's harmless to write to
	 * the bits for cores that are not present.
	 */
	bus_space_write_4(fdtbus_bs_tag, scu, SCU_INV_TAGS_REG, 0x0000ffff);

	/* Make sure all cores except the first are off */
	val = bus_space_read_4(fdtbus_bs_tag, pmu, PMU_PWRDN_CON);
	for (i = 1; i < mp_ncpus; i++)
		val |= 1 << i;
	bus_space_write_4(fdtbus_bs_tag, pmu, PMU_PWRDN_CON, val);

	/* Enable SCU power domain */
	val = bus_space_read_4(fdtbus_bs_tag, pmu, PMU_PWRDN_CON);
	val &= ~PMU_PWRDN_SCU;
	bus_space_write_4(fdtbus_bs_tag, pmu, PMU_PWRDN_CON, val);

	/* Enable SCU */
	val = bus_space_read_4(fdtbus_bs_tag, scu, SCU_CONTROL_REG);
	bus_space_write_4(fdtbus_bs_tag, scu, SCU_CONTROL_REG,
	    val | SCU_CONTROL_ENABLE);

	/*
	 * Cores will execute the code which resides at the start of
	 * the on-chip bootram/sram after power-on. This sram region
	 * should be reserved and the trampoline code that directs
	 * the core to the real startup code in ram should be copied
	 * into this sram region.
	 *
	 * First set boot function for the sram code.
	 */
	mpentry_addr = (char *)pmap_kextract((vm_offset_t)mpentry);

	/* Copy trampoline to sram, that runs during startup of the core */
	bus_space_write_region_4(fdtbus_bs_tag, imem, 0,
	    (uint32_t *)&rk30xx_boot2, 8);

	dcache_wbinv_poc_all();

	/* Start all cores */
	val = bus_space_read_4(fdtbus_bs_tag, pmu, PMU_PWRDN_CON);
	for (i = 1; i < mp_ncpus; i++)
		val &= ~(1 << i);
	bus_space_write_4(fdtbus_bs_tag, pmu, PMU_PWRDN_CON, val);

	dsb();
	sev();

	bus_space_unmap(fdtbus_bs_tag, scu, SCU_SIZE);
	bus_space_unmap(fdtbus_bs_tag, imem, IMEM_SIZE);
	bus_space_unmap(fdtbus_bs_tag, pmu, PMU_SIZE);
}