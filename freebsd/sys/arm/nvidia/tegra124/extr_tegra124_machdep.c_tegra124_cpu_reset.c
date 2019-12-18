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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_CONTROL_REG ; 
 int /*<<< orphan*/  PMC_PHYSBASE ; 
 int /*<<< orphan*/  PMC_SCRATCH0 ; 
 int PMC_SCRATCH0_MODE_BOOTLOADER ; 
 int PMC_SCRATCH0_MODE_MASK ; 
 int /*<<< orphan*/  PMC_SIZE ; 
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  spinlock_enter () ; 

__attribute__((used)) static void
tegra124_cpu_reset(platform_t plat)
{
	bus_space_handle_t pmc;
	uint32_t reg;

	printf("Resetting...\n");
	bus_space_map(fdtbus_bs_tag, PMC_PHYSBASE, PMC_SIZE, 0, &pmc);

	reg = bus_space_read_4(fdtbus_bs_tag, pmc, PMC_SCRATCH0);
	reg &= PMC_SCRATCH0_MODE_MASK;
	bus_space_write_4(fdtbus_bs_tag, pmc, PMC_SCRATCH0,
	   reg | PMC_SCRATCH0_MODE_BOOTLOADER); 	/* boot to bootloader */
	bus_space_read_4(fdtbus_bs_tag, pmc, PMC_SCRATCH0);

	reg = bus_space_read_4(fdtbus_bs_tag, pmc, PMC_CONTROL_REG);
	spinlock_enter();
	dsb();
	bus_space_write_4(fdtbus_bs_tag, pmc, PMC_CONTROL_REG, reg | 0x10);
	bus_space_read_4(fdtbus_bs_tag, pmc, PMC_CONTROL_REG);
	while(1)
		;

}