#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_7__ {scalar_t__ autoneg; } ;
struct TYPE_6__ {scalar_t__ type; int autoneg_advertised; } ;
struct TYPE_8__ {TYPE_2__ mac; TYPE_1__ phy; } ;
struct adapter {scalar_t__ smartspeed; TYPE_3__ hw; scalar_t__ link_active; } ;

/* Variables and functions */
 int ADVERTISE_1000_FULL ; 
 int CR_1000T_MS_ENABLE ; 
 scalar_t__ EM_SMARTSPEED_DOWNSHIFT ; 
 scalar_t__ EM_SMARTSPEED_MAX ; 
 int MII_CR_AUTO_NEG_EN ; 
 int MII_CR_RESTART_AUTO_NEG ; 
 int /*<<< orphan*/  PHY_1000T_CTRL ; 
 int /*<<< orphan*/  PHY_1000T_STATUS ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int SR_1000T_MS_CONFIG_FAULT ; 
 int /*<<< orphan*/  e1000_copper_link_autoneg (TYPE_3__*) ; 
 scalar_t__ e1000_phy_igp ; 
 int /*<<< orphan*/  e1000_read_phy_reg (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lem_smartspeed(struct adapter *adapter)
{
	u16 phy_tmp;

	if (adapter->link_active || (adapter->hw.phy.type != e1000_phy_igp) ||
	    adapter->hw.mac.autoneg == 0 ||
	    (adapter->hw.phy.autoneg_advertised & ADVERTISE_1000_FULL) == 0)
		return;

	if (adapter->smartspeed == 0) {
		/* If Master/Slave config fault is asserted twice,
		 * we assume back-to-back */
		e1000_read_phy_reg(&adapter->hw, PHY_1000T_STATUS, &phy_tmp);
		if (!(phy_tmp & SR_1000T_MS_CONFIG_FAULT))
			return;
		e1000_read_phy_reg(&adapter->hw, PHY_1000T_STATUS, &phy_tmp);
		if (phy_tmp & SR_1000T_MS_CONFIG_FAULT) {
			e1000_read_phy_reg(&adapter->hw,
			    PHY_1000T_CTRL, &phy_tmp);
			if(phy_tmp & CR_1000T_MS_ENABLE) {
				phy_tmp &= ~CR_1000T_MS_ENABLE;
				e1000_write_phy_reg(&adapter->hw,
				    PHY_1000T_CTRL, phy_tmp);
				adapter->smartspeed++;
				if(adapter->hw.mac.autoneg &&
				   !e1000_copper_link_autoneg(&adapter->hw) &&
				   !e1000_read_phy_reg(&adapter->hw,
				    PHY_CONTROL, &phy_tmp)) {
					phy_tmp |= (MII_CR_AUTO_NEG_EN |
						    MII_CR_RESTART_AUTO_NEG);
					e1000_write_phy_reg(&adapter->hw,
					    PHY_CONTROL, phy_tmp);
				}
			}
		}
		return;
	} else if(adapter->smartspeed == EM_SMARTSPEED_DOWNSHIFT) {
		/* If still no link, perhaps using 2/3 pair cable */
		e1000_read_phy_reg(&adapter->hw, PHY_1000T_CTRL, &phy_tmp);
		phy_tmp |= CR_1000T_MS_ENABLE;
		e1000_write_phy_reg(&adapter->hw, PHY_1000T_CTRL, phy_tmp);
		if(adapter->hw.mac.autoneg &&
		   !e1000_copper_link_autoneg(&adapter->hw) &&
		   !e1000_read_phy_reg(&adapter->hw, PHY_CONTROL, &phy_tmp)) {
			phy_tmp |= (MII_CR_AUTO_NEG_EN |
				    MII_CR_RESTART_AUTO_NEG);
			e1000_write_phy_reg(&adapter->hw, PHY_CONTROL, phy_tmp);
		}
	}
	/* Restart process after EM_SMARTSPEED_MAX iterations */
	if(adapter->smartspeed++ == EM_SMARTSPEED_MAX)
		adapter->smartspeed = 0;
}