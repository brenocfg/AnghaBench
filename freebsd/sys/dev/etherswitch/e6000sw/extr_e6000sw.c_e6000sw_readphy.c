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
typedef  int /*<<< orphan*/  e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int E6000SW_NUM_PHY_REGS ; 
 scalar_t__ E6000SW_WAITREADY2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int PHY_DATA_MASK ; 
 int /*<<< orphan*/  REG_GLOBAL2 ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  SMI_CMD_BUSY ; 
 int SMI_CMD_DEV_ADDR ; 
 int SMI_CMD_DEV_ADDR_MASK ; 
 int SMI_CMD_OP_C22_READ ; 
 int SMI_CMD_REG_ADDR_MASK ; 
 int /*<<< orphan*/  SMI_PHY_CMD_REG ; 
 int /*<<< orphan*/  SMI_PHY_DATA_REG ; 
 int /*<<< orphan*/ * device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  e6000sw_is_phyport (int /*<<< orphan*/ *,int) ; 
 int e6000sw_readreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_writereg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
e6000sw_readphy(device_t dev, int phy, int reg)
{
	e6000sw_softc_t *sc;
	uint32_t val;

	sc = device_get_softc(dev);
	if (!e6000sw_is_phyport(sc, phy) || reg >= E6000SW_NUM_PHY_REGS) {
		device_printf(dev, "Wrong register address.\n");
		return (EINVAL);
	}

	E6000SW_LOCK_ASSERT(sc, SA_XLOCKED);
	if (E6000SW_WAITREADY2(sc, SMI_PHY_CMD_REG, SMI_CMD_BUSY)) {
		device_printf(dev, "Timeout while waiting for switch\n");
		return (ETIMEDOUT);
	}

	e6000sw_writereg(sc, REG_GLOBAL2, SMI_PHY_CMD_REG,
	    SMI_CMD_OP_C22_READ | (reg & SMI_CMD_REG_ADDR_MASK) |
	    ((phy << SMI_CMD_DEV_ADDR) & SMI_CMD_DEV_ADDR_MASK));
	if (E6000SW_WAITREADY2(sc, SMI_PHY_CMD_REG, SMI_CMD_BUSY)) {
		device_printf(dev, "Timeout while waiting for switch\n");
		return (ETIMEDOUT);
	}

	val = e6000sw_readreg(sc, REG_GLOBAL2, SMI_PHY_DATA_REG);

	return (val & PHY_DATA_MASK);
}