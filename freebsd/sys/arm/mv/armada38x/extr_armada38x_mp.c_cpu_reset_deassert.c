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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_RESET_ASSERT ; 
 int /*<<< orphan*/  CPU_RESET_OFFSET (int) ; 
 scalar_t__ MV_CPU_RESET_BASE ; 
 int /*<<< orphan*/  MV_CPU_RESET_REGS_LEN ; 
 int bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 

__attribute__((used)) static int
cpu_reset_deassert(void)
{
	bus_space_handle_t vaddr;
	uint32_t reg;
	int rv;

	rv = bus_space_map(fdtbus_bs_tag, (bus_addr_t)MV_CPU_RESET_BASE,
	    MV_CPU_RESET_REGS_LEN, 0, &vaddr);
	if (rv != 0)
		return (rv);

	/* CPU1 is held at reset by default - clear assert bit to release it */
	reg = bus_space_read_4(fdtbus_bs_tag, vaddr, CPU_RESET_OFFSET(1));
	reg &= ~CPU_RESET_ASSERT;

	bus_space_write_4(fdtbus_bs_tag, vaddr, CPU_RESET_OFFSET(1), reg);

	bus_space_unmap(fdtbus_bs_tag, vaddr, MV_CPU_RESET_REGS_LEN);

	return (0);
}