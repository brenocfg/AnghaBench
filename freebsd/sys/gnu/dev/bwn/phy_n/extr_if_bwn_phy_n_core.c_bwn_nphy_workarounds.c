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
struct bwn_phy_n {scalar_t__ hang_avoid; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_BAND_5G ; 
 int /*<<< orphan*/  BWN_NPHY_IQFLIP ; 
 int BWN_NPHY_IQFLIP_ADC1 ; 
 int BWN_NPHY_IQFLIP_ADC2 ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_classifier (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_stay_in_carrier_search (struct bwn_mac*,int) ; 
 int bwn_nphy_workarounds_rev1_2 (struct bwn_mac*) ; 
 int bwn_nphy_workarounds_rev3plus (struct bwn_mac*) ; 
 int bwn_nphy_workarounds_rev7plus (struct bwn_mac*) ; 

__attribute__((used)) static int bwn_nphy_workarounds(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = phy->phy_n;
	int error;

	if (bwn_current_band(mac) == BWN_BAND_5G)
		bwn_nphy_classifier(mac, 1, 0);
	else
		bwn_nphy_classifier(mac, 1, 1);

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, 1);

	BWN_PHY_SET(mac, BWN_NPHY_IQFLIP,
		    BWN_NPHY_IQFLIP_ADC1 | BWN_NPHY_IQFLIP_ADC2);

	/* TODO: rev19+ */
	if (mac->mac_phy.rev >= 7)
		error = bwn_nphy_workarounds_rev7plus(mac);
	else if (mac->mac_phy.rev >= 3)
		error = bwn_nphy_workarounds_rev3plus(mac);
	else
		error = bwn_nphy_workarounds_rev1_2(mac);

	if (error)
		return (error);

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, 0);

	return (0);
}