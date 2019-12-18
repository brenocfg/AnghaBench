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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct ieee80211_channel {int /*<<< orphan*/  ic_ieee; } ;
struct bwn_phy_n_sfo_cfg {int dummy; } ;
struct bwn_phy {int rev; scalar_t__ channel_type; int rf_rev; int /*<<< orphan*/  channel; } ;
struct bwn_nphy_chantabent_rev7_2g {struct bwn_phy_n_sfo_cfg phy_regs; } ;
struct bwn_nphy_chantabent_rev7 {struct bwn_phy_n_sfo_cfg phy_regs; } ;
struct bwn_nphy_channeltab_entry_rev3 {struct bwn_phy_n_sfo_cfg const phy_regs; } ;
struct bwn_nphy_channeltab_entry_rev2 {struct bwn_phy_n_sfo_cfg const phy_regs; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;
typedef  scalar_t__ bwn_chan_type_t ;

/* Variables and functions */
 int B2055_MASTER1 ; 
 scalar_t__ BWN_BAND_5G ; 
 scalar_t__ BWN_CHAN_TYPE_40_HT_D ; 
 scalar_t__ BWN_CHAN_TYPE_40_HT_U ; 
 int BWN_NPHY_RXCTL ; 
 int BWN_NPHY_RXCTL_BSELU20 ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_RF_SETMASK (struct bwn_mac*,int,int,int) ; 
 int ENODEV ; 
 int ESRCH ; 
 int R2057_TIA_CONFIG_CORE0 ; 
 int R2057_TIA_CONFIG_CORE1 ; 
 scalar_t__ bwn_channel_band (struct bwn_mac*,struct ieee80211_channel*) ; 
 scalar_t__ bwn_channel_type_is_40mhz (scalar_t__) ; 
 int /*<<< orphan*/  bwn_get_chan_centre_freq (struct bwn_mac*,struct ieee80211_channel*) ; 
 int bwn_nphy_channel_setup (struct bwn_mac*,struct bwn_phy_n_sfo_cfg const*,struct ieee80211_channel*) ; 
 struct bwn_nphy_channeltab_entry_rev2* bwn_nphy_get_chantabent_rev2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 struct bwn_nphy_channeltab_entry_rev3* bwn_nphy_get_chantabent_rev3 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_radio_2055_setup (struct bwn_mac*,struct bwn_nphy_channeltab_entry_rev2 const*) ; 
 int /*<<< orphan*/  bwn_radio_2056_setup (struct bwn_mac*,struct bwn_nphy_channeltab_entry_rev3 const*) ; 
 int /*<<< orphan*/  bwn_radio_2057_setup (struct bwn_mac*,struct bwn_nphy_chantabent_rev7 const*,struct bwn_nphy_chantabent_rev7_2g const*) ; 
 int /*<<< orphan*/  r2057_get_chantabent_rev7 (struct bwn_mac*,int /*<<< orphan*/ ,struct bwn_nphy_chantabent_rev7 const**,struct bwn_nphy_chantabent_rev7_2g const**) ; 

__attribute__((used)) static int bwn_nphy_set_channel(struct bwn_mac *mac,
				struct ieee80211_channel *channel,
				bwn_chan_type_t channel_type)
{
	struct bwn_phy *phy = &mac->mac_phy;

	const struct bwn_nphy_channeltab_entry_rev2 *tabent_r2 = NULL;
	const struct bwn_nphy_channeltab_entry_rev3 *tabent_r3 = NULL;
	const struct bwn_nphy_chantabent_rev7 *tabent_r7 = NULL;
	const struct bwn_nphy_chantabent_rev7_2g *tabent_r7_2g = NULL;

	int error;
	uint8_t tmp;

	if (phy->rev >= 19) {
		return -ESRCH;
		/* TODO */
	} else if (phy->rev >= 7) {
		r2057_get_chantabent_rev7(mac, bwn_get_chan_centre_freq(mac, channel),
					  &tabent_r7, &tabent_r7_2g);
		if (!tabent_r7 && !tabent_r7_2g)
			return -ESRCH;
	} else if (phy->rev >= 3) {
		tabent_r3 = bwn_nphy_get_chantabent_rev3(mac,
		    bwn_get_chan_centre_freq(mac, channel));
		if (!tabent_r3)
			return -ESRCH;
	} else {
		tabent_r2 = bwn_nphy_get_chantabent_rev2(mac,
		    channel->ic_ieee);
		if (!tabent_r2)
			return -ESRCH;
	}

	/* Channel is set later in common code, but we need to set it on our
	   own to let this function's subcalls work properly. */
#if 0
	phy->channel = channel->ic_ieee;
#endif

#if 0
	if (bwn_channel_type_is_40mhz(phy->channel_type) !=
		bwn_channel_type_is_40mhz(channel_type))
		; /* TODO: BMAC BW Set (channel_type) */
#endif

	if (channel_type == BWN_CHAN_TYPE_40_HT_U) {
		BWN_PHY_SET(mac, BWN_NPHY_RXCTL, BWN_NPHY_RXCTL_BSELU20);
		if (phy->rev >= 7)
			BWN_PHY_SET(mac, 0x310, 0x8000);
	} else if (channel_type == BWN_CHAN_TYPE_40_HT_D) {
		BWN_PHY_MASK(mac, BWN_NPHY_RXCTL, ~BWN_NPHY_RXCTL_BSELU20);
		if (phy->rev >= 7)
			BWN_PHY_MASK(mac, 0x310, (uint16_t)~0x8000);
	}

	if (phy->rev >= 19) {
		/* TODO */
		error = ENODEV;
	} else if (phy->rev >= 7) {
		const struct bwn_phy_n_sfo_cfg *phy_regs = tabent_r7 ?
			&(tabent_r7->phy_regs) : &(tabent_r7_2g->phy_regs);

		if (phy->rf_rev <= 4 || phy->rf_rev == 6) {
			tmp = (bwn_channel_band(mac, channel) == BWN_BAND_5G) ? 2 : 0;
			BWN_RF_SETMASK(mac, R2057_TIA_CONFIG_CORE0, ~2, tmp);
			BWN_RF_SETMASK(mac, R2057_TIA_CONFIG_CORE1, ~2, tmp);
		}

		bwn_radio_2057_setup(mac, tabent_r7, tabent_r7_2g);
		error = bwn_nphy_channel_setup(mac, phy_regs, channel);
	} else if (phy->rev >= 3) {
		tmp = (bwn_channel_band(mac, channel) == BWN_BAND_5G) ? 4 : 0;
		BWN_RF_SETMASK(mac, 0x08, 0xFFFB, tmp);
		bwn_radio_2056_setup(mac, tabent_r3);
		error = bwn_nphy_channel_setup(mac, &(tabent_r3->phy_regs),
		    channel);
	} else {
		tmp = (bwn_channel_band(mac, channel) == BWN_BAND_5G) ? 0x0020 : 0x0050;
		BWN_RF_SETMASK(mac, B2055_MASTER1, 0xFF8F, tmp);
		bwn_radio_2055_setup(mac, tabent_r2);
		error = bwn_nphy_channel_setup(mac, &(tabent_r2->phy_regs),
		    channel);
	}

	return (error);
}