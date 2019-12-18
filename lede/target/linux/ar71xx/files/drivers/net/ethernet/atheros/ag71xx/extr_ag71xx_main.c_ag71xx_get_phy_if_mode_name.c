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
typedef  int phy_interface_t ;

/* Variables and functions */
#define  PHY_INTERFACE_MODE_GMII 132 
#define  PHY_INTERFACE_MODE_MII 131 
#define  PHY_INTERFACE_MODE_RGMII 130 
#define  PHY_INTERFACE_MODE_RMII 129 
#define  PHY_INTERFACE_MODE_SGMII 128 

__attribute__((used)) static const char *ag71xx_get_phy_if_mode_name(phy_interface_t mode)
{
	switch (mode) {
	case PHY_INTERFACE_MODE_MII:
		return "MII";
	case PHY_INTERFACE_MODE_GMII:
		return "GMII";
	case PHY_INTERFACE_MODE_RMII:
		return "RMII";
	case PHY_INTERFACE_MODE_RGMII:
		return "RGMII";
	case PHY_INTERFACE_MODE_SGMII:
		return "SGMII";
	default:
		break;
	}

	return "unknown";
}