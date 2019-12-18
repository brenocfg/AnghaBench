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
struct mii_bus {int (* read ) (struct mii_bus*,int,int) ;int /*<<< orphan*/  (* write ) (struct mii_bus*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int MV_INDIRECT_ADDR_S ; 
 int /*<<< orphan*/  MV_INDIRECT_INPROGRESS ; 
 int MV_INDIRECT_READ ; 
 int /*<<< orphan*/  MV_INDIRECT_REG_CMD ; 
 int MV_INDIRECT_REG_DATA ; 
 int /*<<< orphan*/  mvsw61xx_wait_mask_raw (struct mii_bus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct mii_bus*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct mii_bus*,int,int) ; 

__attribute__((used)) static u16
r16(struct mii_bus *bus, bool indirect, int base_addr, int addr, int reg)
{
	u16 ind_addr;

	if (!indirect)
		return bus->read(bus, addr, reg);

	/* Indirect read: First, make sure switch is free */
	mvsw61xx_wait_mask_raw(bus, base_addr, MV_INDIRECT_REG_CMD,
			MV_INDIRECT_INPROGRESS, 0);

	/* Load address and request read */
	ind_addr = MV_INDIRECT_READ | (addr << MV_INDIRECT_ADDR_S) | reg;
	bus->write(bus, base_addr, MV_INDIRECT_REG_CMD,
			ind_addr);

	/* Wait until it's ready */
	mvsw61xx_wait_mask_raw(bus, base_addr, MV_INDIRECT_REG_CMD,
			MV_INDIRECT_INPROGRESS, 0);

	/* Read the requested data */
	return bus->read(bus, base_addr, MV_INDIRECT_REG_DATA);
}