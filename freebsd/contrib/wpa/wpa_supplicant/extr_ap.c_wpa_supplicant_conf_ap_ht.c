#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_modes; struct hostapd_hw_modes* modes; } ;
struct wpa_supplicant {scalar_t__ wpa_state; scalar_t__ assoc_freq; struct wpa_supplicant* next; TYPE_3__* global; TYPE_1__ hw; } ;
struct wpa_ssid {int frequency; int ht40; scalar_t__ he; int /*<<< orphan*/  mode; scalar_t__ vht; scalar_t__ p2p_group; scalar_t__ ht; scalar_t__ disable_ht; } ;
struct hostapd_hw_modes {scalar_t__ mode; int ht_capab; TYPE_2__* he_capab; int /*<<< orphan*/  vht_capab; } ;
struct hostapd_config {scalar_t__ hw_mode; int ieee80211n; int ht_capab; int secondary_channel; int ieee80211ac; int ieee80211ax; int no_pri_sec_switch; int /*<<< orphan*/  vht_capab; int /*<<< orphan*/  channel; } ;
struct TYPE_6__ {struct wpa_supplicant* ifaces; } ;
struct TYPE_5__ {scalar_t__ he_supported; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 int HT_CAP_INFO_GREEN_FIELD ; 
 int HT_CAP_INFO_MAX_AMSDU_SIZE ; 
 int HT_CAP_INFO_RX_STBC_MASK ; 
 int HT_CAP_INFO_SHORT_GI20MHZ ; 
 int HT_CAP_INFO_SHORT_GI40MHZ ; 
 int HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET ; 
 int HT_CAP_INFO_TX_STBC ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ NUM_HOSTAPD_MODES ; 
 scalar_t__ WPA_AUTHENTICATING ; 
 scalar_t__ ieee80211_freq_to_chan (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpas_conf_ap_vht (struct wpa_supplicant*,struct wpa_ssid*,struct hostapd_config*,struct hostapd_hw_modes*) ; 
 size_t wpas_mode_to_ieee80211_mode (int /*<<< orphan*/ ) ; 
 int wpas_p2p_get_ht40_mode (struct wpa_supplicant*,struct hostapd_hw_modes*,int /*<<< orphan*/ ) ; 

int wpa_supplicant_conf_ap_ht(struct wpa_supplicant *wpa_s,
			      struct wpa_ssid *ssid,
			      struct hostapd_config *conf)
{
	conf->hw_mode = ieee80211_freq_to_chan(ssid->frequency,
					       &conf->channel);

	if (conf->hw_mode == NUM_HOSTAPD_MODES) {
		wpa_printf(MSG_ERROR, "Unsupported AP mode frequency: %d MHz",
			   ssid->frequency);
		return -1;
	}

	/* TODO: enable HT40 if driver supports it;
	 * drop to 11b if driver does not support 11g */

#ifdef CONFIG_IEEE80211N
	/*
	 * Enable HT20 if the driver supports it, by setting conf->ieee80211n
	 * and a mask of allowed capabilities within conf->ht_capab.
	 * Using default config settings for: conf->ht_op_mode_fixed,
	 * conf->secondary_channel, conf->require_ht
	 */
	if (wpa_s->hw.modes) {
		struct hostapd_hw_modes *mode = NULL;
		int i, no_ht = 0;

		wpa_printf(MSG_DEBUG,
			   "Determining HT/VHT options based on driver capabilities (freq=%u chan=%u)",
			   ssid->frequency, conf->channel);

		for (i = 0; i < wpa_s->hw.num_modes; i++) {
			if (wpa_s->hw.modes[i].mode == conf->hw_mode) {
				mode = &wpa_s->hw.modes[i];
				break;
			}
		}

#ifdef CONFIG_HT_OVERRIDES
		if (ssid->disable_ht)
			ssid->ht = 0;
#endif /* CONFIG_HT_OVERRIDES */

		if (!ssid->ht) {
			wpa_printf(MSG_DEBUG,
				   "HT not enabled in network profile");
			conf->ieee80211n = 0;
			conf->ht_capab = 0;
			no_ht = 1;
		}

		if (!no_ht && mode && mode->ht_capab) {
			wpa_printf(MSG_DEBUG,
				   "Enable HT support (p2p_group=%d 11a=%d ht40_hw_capab=%d ssid->ht40=%d)",
				   ssid->p2p_group,
				   conf->hw_mode == HOSTAPD_MODE_IEEE80211A,
				   !!(mode->ht_capab &
				      HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET),
				   ssid->ht40);
			conf->ieee80211n = 1;
#ifdef CONFIG_P2P
			if (ssid->p2p_group &&
			    conf->hw_mode == HOSTAPD_MODE_IEEE80211A &&
			    (mode->ht_capab &
			     HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET) &&
			    ssid->ht40) {
				conf->secondary_channel =
					wpas_p2p_get_ht40_mode(wpa_s, mode,
							       conf->channel);
				wpa_printf(MSG_DEBUG,
					   "HT secondary channel offset %d for P2P group",
					   conf->secondary_channel);
			}
#endif /* CONFIG_P2P */

			if (!ssid->p2p_group &&
			    (mode->ht_capab &
			     HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET)) {
				conf->secondary_channel = ssid->ht40;
				wpa_printf(MSG_DEBUG,
					   "HT secondary channel offset %d for AP",
					   conf->secondary_channel);
			}

			if (conf->secondary_channel)
				conf->ht_capab |=
					HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET;

			/*
			 * white-list capabilities that won't cause issues
			 * to connecting stations, while leaving the current
			 * capabilities intact (currently disabled SMPS).
			 */
			conf->ht_capab |= mode->ht_capab &
				(HT_CAP_INFO_GREEN_FIELD |
				 HT_CAP_INFO_SHORT_GI20MHZ |
				 HT_CAP_INFO_SHORT_GI40MHZ |
				 HT_CAP_INFO_RX_STBC_MASK |
				 HT_CAP_INFO_TX_STBC |
				 HT_CAP_INFO_MAX_AMSDU_SIZE);

			if (mode->vht_capab && ssid->vht) {
				conf->ieee80211ac = 1;
				conf->vht_capab |= mode->vht_capab;
				wpas_conf_ap_vht(wpa_s, ssid, conf, mode);
			}

			if (mode->he_capab[wpas_mode_to_ieee80211_mode(
					    ssid->mode)].he_supported &&
			    ssid->he)
				conf->ieee80211ax = 1;
		}
	}

	if (conf->secondary_channel) {
		struct wpa_supplicant *iface;

		for (iface = wpa_s->global->ifaces; iface; iface = iface->next)
		{
			if (iface == wpa_s ||
			    iface->wpa_state < WPA_AUTHENTICATING ||
			    (int) iface->assoc_freq != ssid->frequency)
				continue;

			/*
			 * Do not allow 40 MHz co-ex PRI/SEC switch to force us
			 * to change our PRI channel since we have an existing,
			 * concurrent connection on that channel and doing
			 * multi-channel concurrency is likely to cause more
			 * harm than using different PRI/SEC selection in
			 * environment with multiple BSSes on these two channels
			 * with mixed 20 MHz or PRI channel selection.
			 */
			conf->no_pri_sec_switch = 1;
		}
	}
#endif /* CONFIG_IEEE80211N */

	return 0;
}