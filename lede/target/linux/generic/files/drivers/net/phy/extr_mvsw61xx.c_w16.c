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
typedef  int u16 ;
struct mii_bus {int /*<<< orphan*/  (* write ) (struct mii_bus*,int,int,int) ;} ;

/* Variables and functions */
 int MV_INDIRECT_ADDR_S ; 
 int /*<<< orphan*/  MV_INDIRECT_INPROGRESS ; 
 int MV_INDIRECT_REG_CMD ; 
 int MV_INDIRECT_REG_DATA ; 
 int MV_INDIRECT_WRITE ; 
 int /*<<< orphan*/  mvsw61xx_wait_mask_raw (struct mii_bus*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mii_bus*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct mii_bus*,int,int,int) ; 

__attribute__((used)) static void
w16(struct mii_bus *bus, bool indirect, int base_addr, int addr,
		int reg, u16 val)
{
	u16 ind_addr;

	if (!indirect) {
		bus->write(bus, addr, reg, val);
		return;
	}

	/* Indirect write: First, make sure switch is free */
	mvsw61xx_wait_mask_raw(bus, base_addr, MV_INDIRECT_REG_CMD,
			MV_INDIRECT_INPROGRESS, 0);

	/* Load the data to be written */
	bus->write(bus, base_addr, MV_INDIRECT_REG_DATA, val);

	/* Wait again for switch to be free */
	mvsw61xx_wait_mask_raw(bus, base_addr, MV_INDIRECT_REG_CMD,
			MV_INDIRECT_INPROGRESS, 0);

	/* Load address, and issue write command */
	ind_addr = MV_INDIRECT_WRITE | (addr << MV_INDIRECT_ADDR_S) | reg;
	bus->write(bus, base_addr, MV_INDIRECT_REG_CMD,
			ind_addr);
}