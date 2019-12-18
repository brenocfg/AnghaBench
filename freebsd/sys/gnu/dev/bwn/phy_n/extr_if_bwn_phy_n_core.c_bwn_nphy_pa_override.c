#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct bwn_phy_n {int rfctrl_intc1_save; int rfctrl_intc2_save; } ;
struct TYPE_2__ {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;
typedef  scalar_t__ bwn_band_t ;

/* Variables and functions */
 scalar_t__ BWN_BAND_5G ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_INTC1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_INTC2 ; 
 void* BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_nphy_pa_override(struct bwn_mac *mac, bool enable)
{
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	bwn_band_t band;
	uint16_t tmp;

	if (!enable) {
		nphy->rfctrl_intc1_save = BWN_PHY_READ(mac,
						       BWN_NPHY_RFCTL_INTC1);
		nphy->rfctrl_intc2_save = BWN_PHY_READ(mac,
						       BWN_NPHY_RFCTL_INTC2);
		band = bwn_current_band(mac);
		if (mac->mac_phy.rev >= 7) {
			tmp = 0x1480;
		} else if (mac->mac_phy.rev >= 3) {
			if (band == BWN_BAND_5G)
				tmp = 0x600;
			else
				tmp = 0x480;
		} else {
			if (band == BWN_BAND_5G)
				tmp = 0x180;
			else
				tmp = 0x120;
		}
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_INTC1, tmp);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_INTC2, tmp);
	} else {
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_INTC1,
				nphy->rfctrl_intc1_save);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_INTC2,
				nphy->rfctrl_intc2_save);
	}
}