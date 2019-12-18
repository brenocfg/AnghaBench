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
typedef  int /*<<< orphan*/  platform_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUCFG_BASE ; 
 int /*<<< orphan*/  CPUCFG_SIZE ; 
 int /*<<< orphan*/  CPUXCFG_BASE ; 
 int /*<<< orphan*/  CPUXCFG_SIZE ; 
 int /*<<< orphan*/  PRCM_BASE ; 
 int /*<<< orphan*/  PRCM_SIZE ; 
 int /*<<< orphan*/  aw_mc_mp_start_ap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sev () ; 

void
a83t_mp_start_ap(platform_t plat)
{
	bus_space_handle_t cpuscfg, cpuxcfg, prcm;

	if (bus_space_map(fdtbus_bs_tag, CPUCFG_BASE, CPUCFG_SIZE,
	    0, &cpuscfg) != 0)
		panic("Couldn't map the CPUCFG\n");
	if (bus_space_map(fdtbus_bs_tag, CPUXCFG_BASE, CPUXCFG_SIZE,
	    0, &cpuxcfg) != 0)
		panic("Couldn't map the CPUXCFG\n");
	if (bus_space_map(fdtbus_bs_tag, PRCM_BASE, PRCM_SIZE, 0,
	    &prcm) != 0)
		panic("Couldn't map the PRCM\n");

	aw_mc_mp_start_ap(cpuscfg, cpuxcfg, prcm);
	dsb();
	sev();
	bus_space_unmap(fdtbus_bs_tag, cpuxcfg, CPUXCFG_SIZE);
	bus_space_unmap(fdtbus_bs_tag, cpuscfg, CPUCFG_SIZE);
	bus_space_unmap(fdtbus_bs_tag, prcm, PRCM_SIZE);
}