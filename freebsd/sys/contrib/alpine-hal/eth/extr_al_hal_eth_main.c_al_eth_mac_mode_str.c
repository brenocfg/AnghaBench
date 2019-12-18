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
typedef  enum al_eth_mac_mode { ____Placeholder_al_eth_mac_mode } al_eth_mac_mode ;

/* Variables and functions */
#define  AL_ETH_MAC_MODE_10G_SGMII 136 
#define  AL_ETH_MAC_MODE_10GbE_Serial 135 
#define  AL_ETH_MAC_MODE_KR_LL_25G 134 
#define  AL_ETH_MAC_MODE_RGMII 133 
#define  AL_ETH_MAC_MODE_SGMII 132 
#define  AL_ETH_MAC_MODE_SGMII_2_5G 131 
#define  AL_ETH_MAC_MODE_XLG_LL_25G 130 
#define  AL_ETH_MAC_MODE_XLG_LL_40G 129 
#define  AL_ETH_MAC_MODE_XLG_LL_50G 128 

__attribute__((used)) static const char *al_eth_mac_mode_str(enum al_eth_mac_mode mode)
{
	switch(mode) {
	case AL_ETH_MAC_MODE_RGMII:
		return "RGMII";
	case AL_ETH_MAC_MODE_SGMII:
		return "SGMII";
	case AL_ETH_MAC_MODE_SGMII_2_5G:
		return "SGMII_2_5G";
	case AL_ETH_MAC_MODE_10GbE_Serial:
		return "KR";
        case AL_ETH_MAC_MODE_KR_LL_25G:
		return "KR_LL_25G";
	case AL_ETH_MAC_MODE_10G_SGMII:
		return "10G_SGMII";
	case AL_ETH_MAC_MODE_XLG_LL_40G:
		return "40G_LL";
	case AL_ETH_MAC_MODE_XLG_LL_50G:
		return "50G_LL";
	case AL_ETH_MAC_MODE_XLG_LL_25G:
		return "25G_LL";
	default:
		return "N/A";
	}
}