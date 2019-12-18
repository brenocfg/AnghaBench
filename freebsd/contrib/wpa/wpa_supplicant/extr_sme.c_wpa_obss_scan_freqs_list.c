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
typedef  int u8 ;
struct TYPE_5__ {int ht_sec_chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_modes; int /*<<< orphan*/  modes; } ;
struct wpa_supplicant {int assoc_freq; TYPE_2__ sme; scalar_t__ current_bss; TYPE_1__ hw; } ;
struct wpa_driver_scan_params {int* freqs; } ;
struct hostapd_hw_modes {int num_channels; TYPE_3__* channels; } ;
struct TYPE_6__ {int flag; int freq; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int /*<<< orphan*/  HOSTAPD_MODE_IEEE80211G ; 
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE ; 
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW ; 
 int const HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK ; 
#define  HT_SEC_CHAN_ABOVE 130 
#define  HT_SEC_CHAN_BELOW 129 
#define  HT_SEC_CHAN_UNKNOWN 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 struct hostapd_hw_modes* get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* os_calloc (int,int) ; 
 int* os_zalloc (int) ; 
 int* wpa_bss_get_ie (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static void wpa_obss_scan_freqs_list(struct wpa_supplicant *wpa_s,
				     struct wpa_driver_scan_params *params)
{
	/* Include only affected channels */
	struct hostapd_hw_modes *mode;
	int count, i;
	int start, end;

	mode = get_mode(wpa_s->hw.modes, wpa_s->hw.num_modes,
			HOSTAPD_MODE_IEEE80211G);
	if (mode == NULL) {
		/* No channels supported in this band - use empty list */
		params->freqs = os_zalloc(sizeof(int));
		return;
	}

	if (wpa_s->sme.ht_sec_chan == HT_SEC_CHAN_UNKNOWN &&
	    wpa_s->current_bss) {
		const u8 *ie;

		ie = wpa_bss_get_ie(wpa_s->current_bss, WLAN_EID_HT_OPERATION);
		if (ie && ie[1] >= 2) {
			u8 o;

			o = ie[3] & HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK;
			if (o == HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE)
				wpa_s->sme.ht_sec_chan = HT_SEC_CHAN_ABOVE;
			else if (o == HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW)
				wpa_s->sme.ht_sec_chan = HT_SEC_CHAN_BELOW;
		}
	}

	start = wpa_s->assoc_freq - 10;
	end = wpa_s->assoc_freq + 10;
	switch (wpa_s->sme.ht_sec_chan) {
	case HT_SEC_CHAN_UNKNOWN:
		/* HT40+ possible on channels 1..9 */
		if (wpa_s->assoc_freq <= 2452)
			start -= 20;
		/* HT40- possible on channels 5-13 */
		if (wpa_s->assoc_freq >= 2432)
			end += 20;
		break;
	case HT_SEC_CHAN_ABOVE:
		end += 20;
		break;
	case HT_SEC_CHAN_BELOW:
		start -= 20;
		break;
	}
	wpa_printf(MSG_DEBUG,
		   "OBSS: assoc_freq %d possible affected range %d-%d",
		   wpa_s->assoc_freq, start, end);

	params->freqs = os_calloc(mode->num_channels + 1, sizeof(int));
	if (params->freqs == NULL)
		return;
	for (count = 0, i = 0; i < mode->num_channels; i++) {
		int freq;

		if (mode->channels[i].flag & HOSTAPD_CHAN_DISABLED)
			continue;
		freq = mode->channels[i].freq;
		if (freq - 10 >= end || freq + 10 <= start)
			continue; /* not affected */
		params->freqs[count++] = freq;
	}
}