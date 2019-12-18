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
 int PCM_PWRGATE_TOGGLE_START ; 
 int /*<<< orphan*/  PMC_PHYSBASE ; 
 int /*<<< orphan*/  PMC_PWRGATE_STATUS ; 
 int /*<<< orphan*/  PMC_PWRGATE_TOGGLE ; 
 int /*<<< orphan*/  PMC_SIZE ; 
 int /*<<< orphan*/  TEGRA_EXCEPTION_VECTORS_BASE ; 
 int /*<<< orphan*/  TEGRA_EXCEPTION_VECTORS_SIZE ; 
 int /*<<< orphan*/  TEGRA_EXCEPTION_VECTOR_ENTRY ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int mp_ncpus ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev () ; 

void
tegra124_mp_start_ap(platform_t plat)
{
	bus_space_handle_t pmc;
	bus_space_handle_t exvec;
	int i;
	uint32_t val;
	uint32_t mask;

	if (bus_space_map(fdtbus_bs_tag, PMC_PHYSBASE, PMC_SIZE, 0, &pmc) != 0)
		panic("Couldn't map the PMC\n");
	if (bus_space_map(fdtbus_bs_tag, TEGRA_EXCEPTION_VECTORS_BASE,
	    TEGRA_EXCEPTION_VECTORS_SIZE, 0, &exvec) != 0)
		panic("Couldn't map the exception vectors\n");

	bus_space_write_4(fdtbus_bs_tag, exvec , TEGRA_EXCEPTION_VECTOR_ENTRY,
			  pmap_kextract((vm_offset_t)mpentry));
	bus_space_read_4(fdtbus_bs_tag, exvec , TEGRA_EXCEPTION_VECTOR_ENTRY);


	/* Wait until POWERGATE is ready (max 20 APB cycles). */
	do {
		val = bus_space_read_4(fdtbus_bs_tag, pmc,
		    PMC_PWRGATE_TOGGLE);
	} while ((val & PCM_PWRGATE_TOGGLE_START) != 0);

	for (i = 1; i < mp_ncpus; i++) {
		val = bus_space_read_4(fdtbus_bs_tag, pmc, PMC_PWRGATE_STATUS);
		mask = 1 << (i + 8);	/* cpu mask */
		if ((val & mask) == 0) {
			/* Wait until POWERGATE is ready (max 20 APB cycles). */
			do {
				val = bus_space_read_4(fdtbus_bs_tag, pmc,
				PMC_PWRGATE_TOGGLE);
			} while ((val & PCM_PWRGATE_TOGGLE_START) != 0);
			bus_space_write_4(fdtbus_bs_tag, pmc,
			    PMC_PWRGATE_TOGGLE,
			    PCM_PWRGATE_TOGGLE_START | (8 + i));

			/* Wait until CPU is powered */
			do {
				val = bus_space_read_4(fdtbus_bs_tag, pmc,
				    PMC_PWRGATE_STATUS);
			} while ((val & mask) == 0);
		}

	}
	dsb();
	sev();
	bus_space_unmap(fdtbus_bs_tag, pmc, PMC_SIZE);
	bus_space_unmap(fdtbus_bs_tag, exvec, TEGRA_EXCEPTION_VECTORS_SIZE);
}