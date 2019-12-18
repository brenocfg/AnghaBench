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
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUS_CL_RST (int) ; 
 int /*<<< orphan*/  CPUX_CL_CTRL0 (int) ; 
 int /*<<< orphan*/  CPUX_CL_RST (int) ; 
 int CPU_PWR_CLAMP_STEPS ; 
 int /*<<< orphan*/  PRCM_CL_PWROFF (int) ; 
 int /*<<< orphan*/  PRCM_CL_PWR_CLAMP (int,int) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 

__attribute__((used)) static void
aw_mc_mp_start_cpu(bus_space_handle_t cpuscfg, bus_space_handle_t cpuxcfg,
    bus_space_handle_t prcm, int cluster, int cpu)
{
	uint32_t val;
	int i;

	/* Assert core reset */
	val = bus_space_read_4(fdtbus_bs_tag, cpuxcfg, CPUX_CL_RST(cluster));
	val &= ~(1 << cpu);
	bus_space_write_4(fdtbus_bs_tag, cpuxcfg, CPUX_CL_RST(cluster), val);

	/* Assert power-on reset */
	val = bus_space_read_4(fdtbus_bs_tag, cpuscfg, CPUS_CL_RST(cluster));
	val &= ~(1 << cpu);
	bus_space_write_4(fdtbus_bs_tag, cpuscfg, CPUS_CL_RST(cluster), val);

	/* Disable automatic L1 cache invalidate at reset */
	val = bus_space_read_4(fdtbus_bs_tag, cpuxcfg, CPUX_CL_CTRL0(cluster));
	val &= ~(1 << cpu);
	bus_space_write_4(fdtbus_bs_tag, cpuxcfg, CPUX_CL_CTRL0(cluster), val);

	/* Release power clamp */
	for (i = 0; i <= CPU_PWR_CLAMP_STEPS; i++)
		bus_space_write_4(fdtbus_bs_tag, prcm,
		    PRCM_CL_PWR_CLAMP(cluster, cpu), 0xff >> i);
	while (bus_space_read_4(fdtbus_bs_tag, prcm,
	    PRCM_CL_PWR_CLAMP(cluster, cpu)) != 0)
		;

	/* Clear power-off gating */
	val = bus_space_read_4(fdtbus_bs_tag, prcm, PRCM_CL_PWROFF(cluster));
	val &= ~(1 << cpu);
	bus_space_write_4(fdtbus_bs_tag, prcm, PRCM_CL_PWROFF(cluster), val);

	/* De-assert power-on reset */
	val = bus_space_read_4(fdtbus_bs_tag, cpuscfg, CPUS_CL_RST(cluster));
	val |= (1 << cpu);
	bus_space_write_4(fdtbus_bs_tag, cpuscfg, CPUS_CL_RST(cluster), val);

	/* De-assert core reset */
	val = bus_space_read_4(fdtbus_bs_tag, cpuxcfg, CPUX_CL_RST(cluster));
	val |= (1 << cpu);
	bus_space_write_4(fdtbus_bs_tag, cpuxcfg, CPUX_CL_RST(cluster), val);
}