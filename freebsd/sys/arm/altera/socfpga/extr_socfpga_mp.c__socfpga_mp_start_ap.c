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
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int MPUMODRST_CPU1 ; 
 int /*<<< orphan*/  RAM_PHYSBASE ; 
 int /*<<< orphan*/  RAM_SIZE ; 
 int /*<<< orphan*/  RSTMGR_A10_MPUMODRST ; 
 int /*<<< orphan*/  RSTMGR_MPUMODRST ; 
 int /*<<< orphan*/  RSTMGR_PHYSBASE ; 
 int /*<<< orphan*/  RSTMGR_SIZE ; 
 int SCU_CONTROL_ENABLE ; 
 int /*<<< orphan*/  SCU_CONTROL_REG ; 
 int /*<<< orphan*/  SCU_DIAG_CONTROL ; 
 int SCU_DIAG_DISABLE_MIGBIT ; 
 int /*<<< orphan*/  SCU_INV_TAGS_REG ; 
 int /*<<< orphan*/  SCU_PHYSBASE ; 
 int /*<<< orphan*/  SCU_PHYSBASE_A10 ; 
 int /*<<< orphan*/  SCU_SIZE ; 
#define  SOCFPGA_ARRIA10 129 
#define  SOCFPGA_CYCLONE5 128 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_region_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 scalar_t__ mpentry ; 
 char* mpentry_addr ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev () ; 
 int /*<<< orphan*/  socfpga_trampoline ; 

__attribute__((used)) static void
_socfpga_mp_start_ap(uint32_t platid)
{
	bus_space_handle_t scu, rst, ram;
	int reg;

	switch (platid) {
#if defined(SOC_ALTERA_ARRIA10)
	case SOCFPGA_ARRIA10:
		if (bus_space_map(fdtbus_bs_tag, SCU_PHYSBASE_A10,
		    SCU_SIZE, 0, &scu) != 0)
			panic("Couldn't map the SCU\n");
		break;
#endif
#if defined(SOC_ALTERA_CYCLONE5)
	case SOCFPGA_CYCLONE5:
		if (bus_space_map(fdtbus_bs_tag, SCU_PHYSBASE,
		    SCU_SIZE, 0, &scu) != 0)
			panic("Couldn't map the SCU\n");
		break;
#endif
	default:
		panic("Unknown platform id %d\n", platid);
	}

	if (bus_space_map(fdtbus_bs_tag, RSTMGR_PHYSBASE,
					RSTMGR_SIZE, 0, &rst) != 0)
		panic("Couldn't map the reset manager (RSTMGR)\n");
	if (bus_space_map(fdtbus_bs_tag, RAM_PHYSBASE,
					RAM_SIZE, 0, &ram) != 0)
		panic("Couldn't map the first physram page\n");

	/* Invalidate SCU cache tags */
	bus_space_write_4(fdtbus_bs_tag, scu,
		SCU_INV_TAGS_REG, 0x0000ffff);

	/*
	 * Erratum ARM/MP: 764369 (problems with cache maintenance).
	 * Setting the "disable-migratory bit" in the undocumented SCU
	 * Diagnostic Control Register helps work around the problem.
	 */
	reg = bus_space_read_4(fdtbus_bs_tag, scu, SCU_DIAG_CONTROL);
	reg |= (SCU_DIAG_DISABLE_MIGBIT);
	bus_space_write_4(fdtbus_bs_tag, scu, SCU_DIAG_CONTROL, reg);

	/* Put CPU1 to reset state */
	switch (platid) {
#if defined(SOC_ALTERA_ARRIA10)
	case SOCFPGA_ARRIA10:
		bus_space_write_4(fdtbus_bs_tag, rst,
		    RSTMGR_A10_MPUMODRST, MPUMODRST_CPU1);
		break;
#endif
#if defined(SOC_ALTERA_CYCLONE5)
	case SOCFPGA_CYCLONE5:
		bus_space_write_4(fdtbus_bs_tag, rst,
		    RSTMGR_MPUMODRST, MPUMODRST_CPU1);
		break;
#endif
	default:
		panic("Unknown platform id %d\n", platid);
	}

	/* Enable the SCU, then clean the cache on this core */
	reg = bus_space_read_4(fdtbus_bs_tag, scu, SCU_CONTROL_REG);
	reg |= (SCU_CONTROL_ENABLE);
	bus_space_write_4(fdtbus_bs_tag, scu, SCU_CONTROL_REG, reg);

	/* Set up trampoline code */
	mpentry_addr = (char *)pmap_kextract((vm_offset_t)mpentry);
	bus_space_write_region_4(fdtbus_bs_tag, ram, 0,
	    (uint32_t *)&socfpga_trampoline, 8);

	dcache_wbinv_poc_all();

	/* Put CPU1 out from reset */
	switch (platid) {
#if defined(SOC_ALTERA_ARRIA10)
	case SOCFPGA_ARRIA10:
		bus_space_write_4(fdtbus_bs_tag, rst,
		    RSTMGR_A10_MPUMODRST, 0);
		break;
#endif
#if defined(SOC_ALTERA_CYCLONE5)
	case SOCFPGA_CYCLONE5:
		bus_space_write_4(fdtbus_bs_tag, rst,
		    RSTMGR_MPUMODRST, 0);
		break;
#endif
	default:
		panic("Unknown platform id %d\n", platid);
	}

	dsb();
	sev();

	bus_space_unmap(fdtbus_bs_tag, scu, SCU_SIZE);
	bus_space_unmap(fdtbus_bs_tag, rst, RSTMGR_SIZE);
	bus_space_unmap(fdtbus_bs_tag, ram, RAM_SIZE);
}