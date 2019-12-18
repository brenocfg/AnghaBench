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
typedef  int uint32_t ;
struct bwn_phy_n {TYPE_1__* pwr_ctl_info; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int idle_tssi_5g; int idle_tssi_2g; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  N_RSSI_TSSI_2G ; 
 int /*<<< orphan*/  N_RSSI_W1 ; 
 scalar_t__ bwn_is_chan_passive (struct bwn_mac*) ; 
 scalar_t__ bwn_nphy_ipa (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_ipa_internal_tssi_setup (struct bwn_mac*) ; 
 int bwn_nphy_poll_rssi (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override (struct bwn_mac*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev19 (struct bwn_mac*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_nphy_rf_ctl_override_rev7 (struct bwn_mac*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_nphy_rssi_select (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_nphy_stop_playback (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_tx_tone (struct bwn_mac*,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void bwn_nphy_tx_power_ctl_idle_tssi(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;

	uint32_t tmp;
	int32_t rssi[4] = { };

	if (bwn_is_chan_passive(mac))
		return;

	if (bwn_nphy_ipa(mac))
		bwn_nphy_ipa_internal_tssi_setup(mac);

	if (phy->rev >= 19)
		bwn_nphy_rf_ctl_override_rev19(mac, 0x1000, 0, 3, false, 0);
	else if (phy->rev >= 7)
		bwn_nphy_rf_ctl_override_rev7(mac, 0x1000, 0, 3, false, 0);
	else if (phy->rev >= 3)
		bwn_nphy_rf_ctl_override(mac, 0x2000, 0, 3, false);

	bwn_nphy_stop_playback(mac);
	bwn_nphy_tx_tone(mac, 4000, 0, false, false, false);
	DELAY(20);
	tmp = bwn_nphy_poll_rssi(mac, N_RSSI_TSSI_2G, rssi, 1);
	bwn_nphy_stop_playback(mac);

	bwn_nphy_rssi_select(mac, 0, N_RSSI_W1);

	if (phy->rev >= 19)
		bwn_nphy_rf_ctl_override_rev19(mac, 0x1000, 0, 3, true, 0);
	else if (phy->rev >= 7)
		bwn_nphy_rf_ctl_override_rev7(mac, 0x1000, 0, 3, true, 0);
	else if (phy->rev >= 3)
		bwn_nphy_rf_ctl_override(mac, 0x2000, 0, 3, true);

	if (phy->rev >= 19) {
		/* TODO */
		return;
	} else if (phy->rev >= 3) {
		nphy->pwr_ctl_info[0].idle_tssi_5g = (tmp >> 24) & 0xFF;
		nphy->pwr_ctl_info[1].idle_tssi_5g = (tmp >> 8) & 0xFF;
	} else {
		nphy->pwr_ctl_info[0].idle_tssi_5g = (tmp >> 16) & 0xFF;
		nphy->pwr_ctl_info[1].idle_tssi_5g = tmp & 0xFF;
	}
	nphy->pwr_ctl_info[0].idle_tssi_2g = (tmp >> 24) & 0xFF;
	nphy->pwr_ctl_info[1].idle_tssi_2g = (tmp >> 8) & 0xFF;
}