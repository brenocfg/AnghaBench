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
struct bwi_phy {int phy_flags; scalar_t__ phy_mode; int phy_rev; } ;
struct bwi_mac {int /*<<< orphan*/  mac_sc; struct bwi_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_MAC_STATUS ; 
 int BWI_PHY_F_CALIBRATED ; 
 int /*<<< orphan*/  CSR_READ_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  bwi_mac_reset (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  bwi_phy_init_11g (struct bwi_mac*) ; 

int
bwi_phy_calibrate(struct bwi_mac *mac)
{
	struct bwi_phy *phy = &mac->mac_phy;

	/* Dummy read */
	CSR_READ_4(mac->mac_sc, BWI_MAC_STATUS);

	/* Don't re-init */
	if (phy->phy_flags & BWI_PHY_F_CALIBRATED)
		return 0;

	if (phy->phy_mode == IEEE80211_MODE_11G && phy->phy_rev == 1) {
		bwi_mac_reset(mac, 0);
		bwi_phy_init_11g(mac);
		bwi_mac_reset(mac, 1);
	}

	phy->phy_flags |= BWI_PHY_F_CALIBRATED;
	return 0;
}