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
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 scalar_t__ MV_SCU_BASE ; 
 int MV_SCU_ENABLE ; 
 int /*<<< orphan*/  MV_SCU_REGS_LEN ; 
 int /*<<< orphan*/  MV_SCU_REG_CTRL ; 
 int MV_SCU_SL_L2_ENABLE ; 
 int bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 

int
armada38x_scu_enable(void)
{
	bus_space_handle_t vaddr_scu;
	int rv;
	uint32_t val;

	rv = bus_space_map(fdtbus_bs_tag, (bus_addr_t)MV_SCU_BASE,
	    MV_SCU_REGS_LEN, 0, &vaddr_scu);
	if (rv != 0)
		return (rv);

	/* Enable SCU */
	val = bus_space_read_4(fdtbus_bs_tag, vaddr_scu, MV_SCU_REG_CTRL);
	if (!(val & MV_SCU_ENABLE)) {
		/* Enable SCU Speculative linefills to L2 */
		val |= MV_SCU_SL_L2_ENABLE;

		bus_space_write_4(fdtbus_bs_tag, vaddr_scu, 0,
		    val | MV_SCU_ENABLE);
	}

	bus_space_unmap(fdtbus_bs_tag, vaddr_scu, MV_SCU_REGS_LEN);
	return (0);
}