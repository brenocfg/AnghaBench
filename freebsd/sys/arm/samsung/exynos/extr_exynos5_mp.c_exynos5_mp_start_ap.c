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
typedef  int /*<<< orphan*/  platform_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int CORE_CONFIG (int) ; 
 int CORE_PWR_EN ; 
 int /*<<< orphan*/  CORE_STATUS (int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ EXYNOS5420_SOC_ID ; 
 int EXYNOS5420_SYSRAM_NS ; 
 int EXYNOS_PMU_BASE ; 
 int EXYNOS_SYSRAM ; 
 int bus_space_map (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 int /*<<< orphan*/  dsb () ; 
 scalar_t__ exynos_get_soc_id () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int mp_ncpus ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sev () ; 

void
exynos5_mp_start_ap(platform_t plat)
{
	bus_addr_t sysram, pmu;
	int err, i, j;
	int status;
	int reg;

	err = bus_space_map(fdtbus_bs_tag, EXYNOS_PMU_BASE, 0x20000, 0, &pmu);
	if (err != 0)
		panic("Couldn't map pmu\n");

	if (exynos_get_soc_id() == EXYNOS5420_SOC_ID)
		reg = EXYNOS5420_SYSRAM_NS;
	else
		reg = EXYNOS_SYSRAM;

	err = bus_space_map(fdtbus_bs_tag, reg, 0x100, 0, &sysram);
	if (err != 0)
		panic("Couldn't map sysram\n");

	/* Give power to CPUs */
	for (i = 1; i < mp_ncpus; i++) {
		bus_space_write_4(fdtbus_bs_tag, pmu, CORE_CONFIG(i),
		    CORE_PWR_EN);

		for (j = 10; j >= 0; j--) {
			status = bus_space_read_4(fdtbus_bs_tag, pmu,
			    CORE_STATUS(i));
			if ((status & CORE_PWR_EN) == CORE_PWR_EN)
				break;
			DELAY(10);
			if (j == 0)
				printf("Can't power on CPU%d\n", i);
		}
	}

	bus_space_write_4(fdtbus_bs_tag, sysram, 0x0,
	    pmap_kextract((vm_offset_t)mpentry));

	dcache_wbinv_poc_all();

	dsb();
	sev();
	bus_space_unmap(fdtbus_bs_tag, sysram, 0x100);
	bus_space_unmap(fdtbus_bs_tag, pmu, 0x20000);
}