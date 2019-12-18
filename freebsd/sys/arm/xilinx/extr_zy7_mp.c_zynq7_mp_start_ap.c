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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_CONTROL_ENABLE ; 
 int /*<<< orphan*/  SCU_CONTROL_REG ; 
 int /*<<< orphan*/  ZYNQ7_CPU1_ENTRY ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev () ; 

void    
zynq7_mp_start_ap(platform_t plat)
{
	bus_space_handle_t scu_handle;
	bus_space_handle_t ocm_handle;
	uint32_t scu_ctrl;

	/* Map in SCU control register. */
	if (bus_space_map(fdtbus_bs_tag, SCU_CONTROL_REG, 4,
			  0, &scu_handle) != 0)
		panic("platform_mp_start_ap: Couldn't map SCU config reg\n");

	/* Set SCU enable bit. */
	scu_ctrl = bus_space_read_4(fdtbus_bs_tag, scu_handle, 0);
	scu_ctrl |= SCU_CONTROL_ENABLE;
	bus_space_write_4(fdtbus_bs_tag, scu_handle, 0, scu_ctrl);

	bus_space_unmap(fdtbus_bs_tag, scu_handle, 4);

	/* Map in magic location to give entry address to CPU1. */
	if (bus_space_map(fdtbus_bs_tag, ZYNQ7_CPU1_ENTRY, 4,
	    0, &ocm_handle) != 0)
		panic("platform_mp_start_ap: Couldn't map OCM\n");

	/* Write start address for CPU1. */
	bus_space_write_4(fdtbus_bs_tag, ocm_handle, 0,
	    pmap_kextract((vm_offset_t)mpentry));

	bus_space_unmap(fdtbus_bs_tag, ocm_handle, 4);

	/*
	 * The SCU is enabled above but I think the second CPU doesn't
	 * turn on filtering until after the wake-up below. I think that's why
	 * things don't work if I don't put these cache ops here.  Also, the
	 * magic location, 0xfffffff0, isn't in the SCU's filtering range so it
	 * needs a write-back too.
	 */
	dcache_wbinv_poc_all();

	/* Wake up CPU1. */
	dsb();
	sev();
}