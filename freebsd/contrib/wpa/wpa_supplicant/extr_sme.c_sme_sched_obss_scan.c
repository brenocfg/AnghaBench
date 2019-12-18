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
struct TYPE_4__ {int obss_scan_int; int /*<<< orphan*/  ht_sec_chan; scalar_t__ sched_obss_scan; } ;
struct TYPE_3__ {int num_modes; struct hostapd_hw_modes* modes; } ;
struct wpa_supplicant {int drv_flags; TYPE_2__ sme; struct wpa_bss* current_bss; TYPE_1__ hw; struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {scalar_t__ mode; } ;
struct wpa_bss {int freq; } ;
struct hostapd_hw_modes {scalar_t__ mode; int ht_capab; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_MODE_IEEE80211G ; 
 int HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET ; 
 int /*<<< orphan*/  HT_SEC_CHAN_UNKNOWN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAP ; 
 int /*<<< orphan*/  WLAN_EID_OVERLAPPING_BSS_SCAN_PARAMS ; 
 scalar_t__ WPAS_MODE_INFRA ; 
 int WPA_DRIVER_FLAGS_OBSS_SCAN ; 
 int WPA_DRIVER_FLAGS_SME ; 
 int WPA_GET_LE16 (int const*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sme_obss_scan_timeout ; 
 int* wpa_bss_get_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

void sme_sched_obss_scan(struct wpa_supplicant *wpa_s, int enable)
{
	const u8 *ie;
	struct wpa_bss *bss = wpa_s->current_bss;
	struct wpa_ssid *ssid = wpa_s->current_ssid;
	struct hostapd_hw_modes *hw_mode = NULL;
	int i;

	eloop_cancel_timeout(sme_obss_scan_timeout, wpa_s, NULL);
	wpa_s->sme.sched_obss_scan = 0;
	wpa_s->sme.ht_sec_chan = HT_SEC_CHAN_UNKNOWN;
	if (!enable)
		return;

	/*
	 * Schedule OBSS scan if driver is using station SME in wpa_supplicant
	 * or it expects OBSS scan to be performed by wpa_supplicant.
	 */
	if (!((wpa_s->drv_flags & WPA_DRIVER_FLAGS_SME) ||
	      (wpa_s->drv_flags & WPA_DRIVER_FLAGS_OBSS_SCAN)) ||
	    ssid == NULL || ssid->mode != WPAS_MODE_INFRA)
		return;

	if (!wpa_s->hw.modes)
		return;

	/* only HT caps in 11g mode are relevant */
	for (i = 0; i < wpa_s->hw.num_modes; i++) {
		hw_mode = &wpa_s->hw.modes[i];
		if (hw_mode->mode == HOSTAPD_MODE_IEEE80211G)
			break;
	}

	/* Driver does not support HT40 for 11g or doesn't have 11g. */
	if (i == wpa_s->hw.num_modes || !hw_mode ||
	    !(hw_mode->ht_capab & HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET))
		return;

	if (bss == NULL || bss->freq < 2400 || bss->freq > 2500)
		return; /* Not associated on 2.4 GHz band */

	/* Check whether AP supports HT40 */
	ie = wpa_bss_get_ie(wpa_s->current_bss, WLAN_EID_HT_CAP);
	if (!ie || ie[1] < 2 ||
	    !(WPA_GET_LE16(ie + 2) & HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET))
		return; /* AP does not support HT40 */

	ie = wpa_bss_get_ie(wpa_s->current_bss,
			    WLAN_EID_OVERLAPPING_BSS_SCAN_PARAMS);
	if (!ie || ie[1] < 14)
		return; /* AP does not request OBSS scans */

	wpa_s->sme.obss_scan_int = WPA_GET_LE16(ie + 6);
	if (wpa_s->sme.obss_scan_int < 10) {
		wpa_printf(MSG_DEBUG, "SME: Invalid OBSS Scan Interval %u "
			   "replaced with the minimum 10 sec",
			   wpa_s->sme.obss_scan_int);
		wpa_s->sme.obss_scan_int = 10;
	}
	wpa_printf(MSG_DEBUG, "SME: OBSS Scan Interval %u sec",
		   wpa_s->sme.obss_scan_int);
	eloop_register_timeout(wpa_s->sme.obss_scan_int, 0,
			       sme_obss_scan_timeout, wpa_s, NULL);
}