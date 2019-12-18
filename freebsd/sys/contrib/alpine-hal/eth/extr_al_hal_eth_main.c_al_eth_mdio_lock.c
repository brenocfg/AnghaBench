#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct al_hal_eth_adapter {scalar_t__ shared_mdio_if; TYPE_2__* mac_regs_base; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdio_1; int /*<<< orphan*/  mdio_ctrl_1; } ;
struct TYPE_4__ {TYPE_1__ gen; } ;

/* Variables and functions */
 int AL_BIT (int /*<<< orphan*/ ) ; 
 int AL_ETH_MDIO_DELAY_COUNT ; 
 int /*<<< orphan*/  AL_ETH_MDIO_DELAY_PERIOD ; 
 scalar_t__ AL_FALSE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,int) ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int al_eth_mdio_lock(struct al_hal_eth_adapter *adapter)
{
	int	count = 0;
	uint32_t mdio_ctrl_1;

	if (adapter->shared_mdio_if == AL_FALSE)
		return 0; /* nothing to do when interface is not shared */

	do {
		mdio_ctrl_1 = al_reg_read32(&adapter->mac_regs_base->gen.mdio_ctrl_1);
/*
		if (mdio_cfg_status & AL_BIT(1)){ //error
			al_err(" %s mdio read failed on error. phy_addr 0x%x reg 0x%x\n",
				udma_params.name, phy_addr, reg);
			return -EIO;
		}*/
		if (mdio_ctrl_1 & AL_BIT(0)){
			if (count > 0)
				al_dbg("eth %s mdio interface still busy!\n", adapter->name);
		}else{
			return 0;
		}
		al_udelay(AL_ETH_MDIO_DELAY_PERIOD);
	}while(count++ < (AL_ETH_MDIO_DELAY_COUNT * 4));
	al_err(" %s mdio failed to take ownership. MDIO info reg: 0x%08x\n",
		adapter->name, al_reg_read32(&adapter->mac_regs_base->gen.mdio_1));

	return -ETIMEDOUT;
}