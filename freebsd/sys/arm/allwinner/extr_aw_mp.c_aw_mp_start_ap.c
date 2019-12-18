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
 int /*<<< orphan*/  A20_CPU1_PWROFF_REG ; 
 int /*<<< orphan*/  A20_CPU1_PWR_CLAMP ; 
 int /*<<< orphan*/  A20_CPUCFG_BASE ; 
 int ALLWINNERSOC_SUN7I ; 
 int /*<<< orphan*/  CPUCFG_BASE ; 
 int /*<<< orphan*/  CPUCFG_DBGCTL1 ; 
 int /*<<< orphan*/  CPUCFG_GENCTL ; 
 int /*<<< orphan*/  CPUCFG_P_REG0 ; 
 int /*<<< orphan*/  CPUCFG_SIZE ; 
 int CPU_CORE_RESET ; 
 int /*<<< orphan*/  CPU_PWROFF ; 
 int /*<<< orphan*/  CPU_PWR_CLAMP (int) ; 
 int CPU_PWR_CLAMP_STEPS ; 
 int CPU_RESET ; 
 int /*<<< orphan*/  CPU_RST_CTL (int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PRCM_BASE ; 
 int /*<<< orphan*/  PRCM_SIZE ; 
 int allwinner_soc_family () ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int mp_ncpus ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev () ; 

void
aw_mp_start_ap(platform_t plat)
{
	bus_space_handle_t cpucfg;
	bus_space_handle_t prcm;
	int i, j, soc_family;
	uint32_t val;

	soc_family = allwinner_soc_family();
	if (soc_family == ALLWINNERSOC_SUN7I) {
		if (bus_space_map(fdtbus_bs_tag, A20_CPUCFG_BASE, CPUCFG_SIZE,
		    0, &cpucfg) != 0)
			panic("Couldn't map the CPUCFG\n");
	} else {
		if (bus_space_map(fdtbus_bs_tag, CPUCFG_BASE, CPUCFG_SIZE,
		    0, &cpucfg) != 0)
			panic("Couldn't map the CPUCFG\n");
		if (bus_space_map(fdtbus_bs_tag, PRCM_BASE, PRCM_SIZE, 0,
		    &prcm) != 0)
			panic("Couldn't map the PRCM\n");
	}

	dcache_wbinv_poc_all();

	bus_space_write_4(fdtbus_bs_tag, cpucfg, CPUCFG_P_REG0,
	    pmap_kextract((vm_offset_t)mpentry));

	/*
	 * Assert nCOREPORESET low and set L1RSTDISABLE low.
	 * Ensure DBGPWRDUP is set to LOW to prevent any external
	 * debug access to the processor.
	 */
	for (i = 1; i < mp_ncpus; i++)
		bus_space_write_4(fdtbus_bs_tag, cpucfg, CPU_RST_CTL(i), 0);

	/* Set L1RSTDISABLE low */
	val = bus_space_read_4(fdtbus_bs_tag, cpucfg, CPUCFG_GENCTL);
	for (i = 1; i < mp_ncpus; i++)
		val &= ~(1 << i);
	bus_space_write_4(fdtbus_bs_tag, cpucfg, CPUCFG_GENCTL, val);

	/* Set DBGPWRDUP low */
	val = bus_space_read_4(fdtbus_bs_tag, cpucfg, CPUCFG_DBGCTL1);
	for (i = 1; i < mp_ncpus; i++)
		val &= ~(1 << i);
	bus_space_write_4(fdtbus_bs_tag, cpucfg, CPUCFG_DBGCTL1, val);

	/* Release power clamp */
	for (i = 1; i < mp_ncpus; i++)
		for (j = 0; j <= CPU_PWR_CLAMP_STEPS; j++) {
			if (soc_family != ALLWINNERSOC_SUN7I) {
				bus_space_write_4(fdtbus_bs_tag, prcm,
				    CPU_PWR_CLAMP(i), 0xff >> j);
			} else {
				bus_space_write_4(fdtbus_bs_tag,
				    cpucfg, A20_CPU1_PWR_CLAMP, 0xff >> j);
			}
		}
	DELAY(10000);

	/* Clear power-off gating */
	if (soc_family != ALLWINNERSOC_SUN7I) {
		val = bus_space_read_4(fdtbus_bs_tag, prcm, CPU_PWROFF);
		for (i = 0; i < mp_ncpus; i++)
			val &= ~(1 << i);
		bus_space_write_4(fdtbus_bs_tag, prcm, CPU_PWROFF, val);
	} else {
		val = bus_space_read_4(fdtbus_bs_tag,
		    cpucfg, A20_CPU1_PWROFF_REG);
		val &= ~(1 << 0);
		bus_space_write_4(fdtbus_bs_tag, cpucfg,
		    A20_CPU1_PWROFF_REG, val);
	}
	DELAY(1000);

	/* De-assert cpu core reset */
	for (i = 1; i < mp_ncpus; i++)
		bus_space_write_4(fdtbus_bs_tag, cpucfg, CPU_RST_CTL(i),
		    CPU_RESET | CPU_CORE_RESET);

	/* Assert DBGPWRDUP signal */
	val = bus_space_read_4(fdtbus_bs_tag, cpucfg, CPUCFG_DBGCTL1);
	for (i = 1; i < mp_ncpus; i++)
		val |= (1 << i);
	bus_space_write_4(fdtbus_bs_tag, cpucfg, CPUCFG_DBGCTL1, val);

	dsb();
	sev();
	bus_space_unmap(fdtbus_bs_tag, cpucfg, CPUCFG_SIZE);
	if (soc_family != ALLWINNERSOC_SUN7I)
		bus_space_unmap(fdtbus_bs_tag, prcm, PRCM_SIZE);
}