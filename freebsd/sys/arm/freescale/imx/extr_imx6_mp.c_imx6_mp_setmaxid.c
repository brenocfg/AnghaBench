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
 int /*<<< orphan*/  SCU_CONFIG_REG ; 
 int SCU_CONFIG_REG_NCPU_MASK ; 
 int /*<<< orphan*/  SCU_PHYSBASE ; 
 int /*<<< orphan*/  SCU_SIZE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int mp_maxid ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  panic (char*) ; 

void
imx6_mp_setmaxid(platform_t plat)
{
	bus_space_handle_t scu;
	int hwcpu, ncpu;
	uint32_t val;

	/* If we've already set the global vars don't bother to do it again. */
	if (mp_ncpus != 0)
		return;

	if (bus_space_map(fdtbus_bs_tag, SCU_PHYSBASE, SCU_SIZE, 0, &scu) != 0)
		panic("Couldn't map the SCU\n");
	val = bus_space_read_4(fdtbus_bs_tag, scu, SCU_CONFIG_REG);
	hwcpu = (val & SCU_CONFIG_REG_NCPU_MASK) + 1;
	bus_space_unmap(fdtbus_bs_tag, scu, SCU_SIZE);

	ncpu = hwcpu;
	TUNABLE_INT_FETCH("hw.ncpu", &ncpu);
	if (ncpu < 1 || ncpu > hwcpu)
		ncpu = hwcpu;

	mp_ncpus = ncpu;
	mp_maxid = ncpu - 1;
}