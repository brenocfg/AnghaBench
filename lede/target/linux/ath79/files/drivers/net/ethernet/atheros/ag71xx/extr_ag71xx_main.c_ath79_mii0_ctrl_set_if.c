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
struct ag71xx {int phy_if_mode; } ;

/* Variables and functions */
 unsigned int AR71XX_MII0_CTRL_IF_GMII ; 
 unsigned int AR71XX_MII0_CTRL_IF_MII ; 
 unsigned int AR71XX_MII0_CTRL_IF_RGMII ; 
 unsigned int AR71XX_MII0_CTRL_IF_RMII ; 
#define  PHY_INTERFACE_MODE_GMII 131 
#define  PHY_INTERFACE_MODE_MII 130 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  ath79_mii_ctrl_set_if (struct ag71xx*,unsigned int) ; 

__attribute__((used)) static void ath79_mii0_ctrl_set_if(struct ag71xx *ag)
{
	unsigned int mii_if;

	switch (ag->phy_if_mode) {
	case PHY_INTERFACE_MODE_MII:
		mii_if = AR71XX_MII0_CTRL_IF_MII;
		break;
	case PHY_INTERFACE_MODE_GMII:
		mii_if = AR71XX_MII0_CTRL_IF_GMII;
		break;
	case PHY_INTERFACE_MODE_RGMII:
		mii_if = AR71XX_MII0_CTRL_IF_RGMII;
		break;
	case PHY_INTERFACE_MODE_RMII:
		mii_if = AR71XX_MII0_CTRL_IF_RMII;
		break;
	default:
		WARN(1, "Impossible PHY mode defined.\n");
		return;
	}

	ath79_mii_ctrl_set_if(ag, mii_if);
}