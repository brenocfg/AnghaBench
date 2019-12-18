#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct wpabuf {int dummy; } ;
struct wpa_ssid_value {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct hostapd_data {TYPE_4__* iconf; int /*<<< orphan*/  own_addr; TYPE_3__* iface; TYPE_2__* conf; } ;
typedef  enum nr_chan_width { ____Placeholder_nr_chan_width } nr_chan_width ;
struct TYPE_10__ {int ieee80211ax; int secondary_channel; int /*<<< orphan*/  stationary_ap; int /*<<< orphan*/  civic; int /*<<< orphan*/  lci; scalar_t__ ieee80211ac; scalar_t__ ieee80211n; } ;
struct TYPE_9__ {int drv_flags; scalar_t__ freq; } ;
struct TYPE_7__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  ssid_len; } ;
struct TYPE_8__ {int* radio_measurements; TYPE_1__ ssid; scalar_t__ wmm_uapsd; scalar_t__ wmm_enabled; int /*<<< orphan*/  disable_11ac; int /*<<< orphan*/  disable_11n; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int NEI_REP_BSSID_INFO_APSD ; 
 int NEI_REP_BSSID_INFO_DELAYED_BA ; 
 int NEI_REP_BSSID_INFO_HT ; 
 int NEI_REP_BSSID_INFO_KEY_SCOPE ; 
 int NEI_REP_BSSID_INFO_QOS ; 
 int NEI_REP_BSSID_INFO_RM ; 
 int NEI_REP_BSSID_INFO_SECURITY ; 
 int NEI_REP_BSSID_INFO_SPECTRUM_MGMT ; 
 int NEI_REP_BSSID_INFO_VHT ; 
 int NR_CHAN_WIDTH_80P80 ; 
 scalar_t__ NUM_HOSTAPD_MODES ; 
 int WLAN_CAPABILITY_SPECTRUM_MGMT ; 
 int WLAN_RRM_CAPS_NEIGHBOR_REPORT ; 
 int WNM_NEIGHBOR_WIDE_BW_CHAN ; 
 int WPA_DRIVER_FLAGS_AP_UAPSD ; 
 int hostapd_get_nr_chan_width (struct hostapd_data*,int,int,int) ; 
 int hostapd_get_oper_centr_freq_seg0_idx (TYPE_4__*) ; 
 int hostapd_get_oper_centr_freq_seg1_idx (TYPE_4__*) ; 
 int /*<<< orphan*/  hostapd_get_oper_chwidth (TYPE_4__*) ; 
 int /*<<< orphan*/  hostapd_neighbor_set (struct hostapd_data*,int /*<<< orphan*/ ,struct wpa_ssid_value*,struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hostapd_own_capab_info (struct hostapd_data*) ; 
 int /*<<< orphan*/  ieee80211_freq_to_chan (scalar_t__,int*) ; 
 scalar_t__ ieee80211_freq_to_channel_ext (scalar_t__,int,int /*<<< orphan*/ ,int*,int*) ; 
 int ieee80211_get_phy_type (scalar_t__,int,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_le32 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

void hostapd_neighbor_set_own_report(struct hostapd_data *hapd)
{
#ifdef NEED_AP_MLME
	u16 capab = hostapd_own_capab_info(hapd);
	int ht = hapd->iconf->ieee80211n && !hapd->conf->disable_11n;
	int vht = hapd->iconf->ieee80211ac && !hapd->conf->disable_11ac;
	int he = hapd->iconf->ieee80211ax;
	struct wpa_ssid_value ssid;
	u8 channel, op_class;
	u8 center_freq1_idx = 0, center_freq2_idx = 0;
	enum nr_chan_width width;
	u32 bssid_info;
	struct wpabuf *nr;

	if (!(hapd->conf->radio_measurements[0] &
	      WLAN_RRM_CAPS_NEIGHBOR_REPORT))
		return;

	bssid_info = 3; /* AP is reachable */
	bssid_info |= NEI_REP_BSSID_INFO_SECURITY; /* "same as the AP" */
	bssid_info |= NEI_REP_BSSID_INFO_KEY_SCOPE; /* "same as the AP" */

	if (capab & WLAN_CAPABILITY_SPECTRUM_MGMT)
		bssid_info |= NEI_REP_BSSID_INFO_SPECTRUM_MGMT;

	bssid_info |= NEI_REP_BSSID_INFO_RM; /* RRM is supported */

	if (hapd->conf->wmm_enabled) {
		bssid_info |= NEI_REP_BSSID_INFO_QOS;

		if (hapd->conf->wmm_uapsd &&
		    (hapd->iface->drv_flags & WPA_DRIVER_FLAGS_AP_UAPSD))
			bssid_info |= NEI_REP_BSSID_INFO_APSD;
	}

	if (ht) {
		bssid_info |= NEI_REP_BSSID_INFO_HT |
			NEI_REP_BSSID_INFO_DELAYED_BA;

		/* VHT bit added in IEEE P802.11-REVmc/D4.3 */
		if (vht)
			bssid_info |= NEI_REP_BSSID_INFO_VHT;
	}

	/* TODO: Set NEI_REP_BSSID_INFO_MOBILITY_DOMAIN if MDE is set */

	if (ieee80211_freq_to_channel_ext(hapd->iface->freq,
					  hapd->iconf->secondary_channel,
					  hostapd_get_oper_chwidth(hapd->iconf),
					  &op_class, &channel) ==
	    NUM_HOSTAPD_MODES)
		return;
	width = hostapd_get_nr_chan_width(hapd, ht, vht, he);
	if (vht) {
		center_freq1_idx = hostapd_get_oper_centr_freq_seg0_idx(
			hapd->iconf);
		if (width == NR_CHAN_WIDTH_80P80)
			center_freq2_idx =
				hostapd_get_oper_centr_freq_seg1_idx(
					hapd->iconf);
	} else if (ht) {
		ieee80211_freq_to_chan(hapd->iface->freq +
				       10 * hapd->iconf->secondary_channel,
				       &center_freq1_idx);
	}

	ssid.ssid_len = hapd->conf->ssid.ssid_len;
	os_memcpy(ssid.ssid, hapd->conf->ssid.ssid, ssid.ssid_len);

	/*
	 * Neighbor Report element size = BSSID + BSSID info + op_class + chan +
	 * phy type + wide bandwidth channel subelement.
	 */
	nr = wpabuf_alloc(ETH_ALEN + 4 + 1 + 1 + 1 + 5);
	if (!nr)
		return;

	wpabuf_put_data(nr, hapd->own_addr, ETH_ALEN);
	wpabuf_put_le32(nr, bssid_info);
	wpabuf_put_u8(nr, op_class);
	wpabuf_put_u8(nr, channel);
	wpabuf_put_u8(nr, ieee80211_get_phy_type(hapd->iface->freq, ht, vht));

	/*
	 * Wide Bandwidth Channel subelement may be needed to allow the
	 * receiving STA to send packets to the AP. See IEEE P802.11-REVmc/D5.0
	 * Figure 9-301.
	 */
	wpabuf_put_u8(nr, WNM_NEIGHBOR_WIDE_BW_CHAN);
	wpabuf_put_u8(nr, 3);
	wpabuf_put_u8(nr, width);
	wpabuf_put_u8(nr, center_freq1_idx);
	wpabuf_put_u8(nr, center_freq2_idx);

	hostapd_neighbor_set(hapd, hapd->own_addr, &ssid, nr, hapd->iconf->lci,
			     hapd->iconf->civic, hapd->iconf->stationary_ap);

	wpabuf_free(nr);
#endif /* NEED_AP_MLME */
}