#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int num_modes; struct hostapd_hw_modes* modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct wpa_bss {scalar_t__ freq; } ;
struct hostapd_hw_modes {int num_channels; scalar_t__ mode; int num_rates; int* rates; TYPE_2__* channels; } ;
typedef  int /*<<< orphan*/  scan_ie ;
struct TYPE_4__ {int freq; } ;

/* Variables and functions */
 int const BSS_MEMBERSHIP_SELECTOR_HT_PHY ; 
 int const BSS_MEMBERSHIP_SELECTOR_VHT_PHY ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211G ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int const WLAN_EID_EXT_SUPP_RATES ; 
 int const WLAN_EID_SUPP_RATES ; 
 int /*<<< orphan*/  ht_supported (struct hostapd_hw_modes const*) ; 
 int /*<<< orphan*/  vht_supported (struct hostapd_hw_modes const*) ; 
 int* wpa_bss_get_ie (struct wpa_bss*,int const) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int rate_match(struct wpa_supplicant *wpa_s, struct wpa_bss *bss,
		      int debug_print)
{
	const struct hostapd_hw_modes *mode = NULL, *modes;
	const u8 scan_ie[2] = { WLAN_EID_SUPP_RATES, WLAN_EID_EXT_SUPP_RATES };
	const u8 *rate_ie;
	int i, j, k;

	if (bss->freq == 0)
		return 1; /* Cannot do matching without knowing band */

	modes = wpa_s->hw.modes;
	if (modes == NULL) {
		/*
		 * The driver does not provide any additional information
		 * about the utilized hardware, so allow the connection attempt
		 * to continue.
		 */
		return 1;
	}

	for (i = 0; i < wpa_s->hw.num_modes; i++) {
		for (j = 0; j < modes[i].num_channels; j++) {
			int freq = modes[i].channels[j].freq;
			if (freq == bss->freq) {
				if (mode &&
				    mode->mode == HOSTAPD_MODE_IEEE80211G)
					break; /* do not allow 802.11b replace
						* 802.11g */
				mode = &modes[i];
				break;
			}
		}
	}

	if (mode == NULL)
		return 0;

	for (i = 0; i < (int) sizeof(scan_ie); i++) {
		rate_ie = wpa_bss_get_ie(bss, scan_ie[i]);
		if (rate_ie == NULL)
			continue;

		for (j = 2; j < rate_ie[1] + 2; j++) {
			int flagged = !!(rate_ie[j] & 0x80);
			int r = (rate_ie[j] & 0x7f) * 5;

			/*
			 * IEEE Std 802.11n-2009 7.3.2.2:
			 * The new BSS Membership selector value is encoded
			 * like a legacy basic rate, but it is not a rate and
			 * only indicates if the BSS members are required to
			 * support the mandatory features of Clause 20 [HT PHY]
			 * in order to join the BSS.
			 */
			if (flagged && ((rate_ie[j] & 0x7f) ==
					BSS_MEMBERSHIP_SELECTOR_HT_PHY)) {
				if (!ht_supported(mode)) {
					if (debug_print)
						wpa_dbg(wpa_s, MSG_DEBUG,
							"   hardware does not support HT PHY");
					return 0;
				}
				continue;
			}

			/* There's also a VHT selector for 802.11ac */
			if (flagged && ((rate_ie[j] & 0x7f) ==
					BSS_MEMBERSHIP_SELECTOR_VHT_PHY)) {
				if (!vht_supported(mode)) {
					if (debug_print)
						wpa_dbg(wpa_s, MSG_DEBUG,
							"   hardware does not support VHT PHY");
					return 0;
				}
				continue;
			}

			if (!flagged)
				continue;

			/* check for legacy basic rates */
			for (k = 0; k < mode->num_rates; k++) {
				if (mode->rates[k] == r)
					break;
			}
			if (k == mode->num_rates) {
				/*
				 * IEEE Std 802.11-2007 7.3.2.2 demands that in
				 * order to join a BSS all required rates
				 * have to be supported by the hardware.
				 */
				if (debug_print)
					wpa_dbg(wpa_s, MSG_DEBUG,
						"   hardware does not support required rate %d.%d Mbps (freq=%d mode==%d num_rates=%d)",
						r / 10, r % 10,
						bss->freq, mode->mode, mode->num_rates);
				return 0;
			}
		}
	}

	return 1;
}