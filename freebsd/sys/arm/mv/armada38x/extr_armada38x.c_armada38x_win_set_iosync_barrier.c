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
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  MV_CPU_SUBSYS_REGS_LEN ; 
 scalar_t__ MV_MBUS_BRIDGE_BASE ; 
 int /*<<< orphan*/  MV_SYNC_BARRIER_CTRL ; 
 int /*<<< orphan*/  MV_SYNC_BARRIER_CTRL_ALL ; 
 int /*<<< orphan*/  bus_space_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 

int
armada38x_win_set_iosync_barrier(void)
{
	bus_space_handle_t vaddr_iowind;
	int rv;

	rv = bus_space_map(fdtbus_bs_tag, (bus_addr_t)MV_MBUS_BRIDGE_BASE,
	    MV_CPU_SUBSYS_REGS_LEN, 0, &vaddr_iowind);
	if (rv != 0)
		return (rv);

	/* Set Sync Barrier flags for all Mbus internal units */
	bus_space_write_4(fdtbus_bs_tag, vaddr_iowind, MV_SYNC_BARRIER_CTRL,
	    MV_SYNC_BARRIER_CTRL_ALL);

	bus_space_barrier(fdtbus_bs_tag, vaddr_iowind, 0,
	    MV_CPU_SUBSYS_REGS_LEN, BUS_SPACE_BARRIER_WRITE);
	bus_space_unmap(fdtbus_bs_tag, vaddr_iowind, MV_CPU_SUBSYS_REGS_LEN);

	return (rv);
}