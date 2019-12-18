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
typedef  int /*<<< orphan*/  u16 ;
struct gsw_mt753x {int phy_base; int /*<<< orphan*/  mii_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_CMD_ADDR ; 
 int /*<<< orphan*/  MDIO_CMD_READ_C45 ; 
 int /*<<< orphan*/  MDIO_ST_C45 ; 
 int MT753X_NUM_PHYS ; 
 int MT753X_SMI_ADDR_MASK ; 
 int mt753x_mii_rw (struct gsw_mt753x*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mt753x_mmd_read(struct gsw_mt753x *gsw, int addr, int devad, u16 reg)
{
	int val;

	if (addr < MT753X_NUM_PHYS)
		addr = (gsw->phy_base + addr) & MT753X_SMI_ADDR_MASK;

	mutex_lock(&gsw->mii_lock);
	mt753x_mii_rw(gsw, addr, devad, reg, MDIO_CMD_ADDR, MDIO_ST_C45);
	val = mt753x_mii_rw(gsw, addr, devad, 0, MDIO_CMD_READ_C45,
			    MDIO_ST_C45);
	mutex_unlock(&gsw->mii_lock);

	return val;
}