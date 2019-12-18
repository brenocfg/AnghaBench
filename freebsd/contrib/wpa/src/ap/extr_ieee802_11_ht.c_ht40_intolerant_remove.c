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
struct sta_info {scalar_t__ ht40_intolerant_set; } ;
struct hostapd_iface {scalar_t__ num_sta_ht40_intolerant; int drv_flags; TYPE_1__* conf; } ;
struct TYPE_2__ {int ht_capab; unsigned int obss_interval; } ;

/* Variables and functions */
 int HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 unsigned int OVERLAPPING_BSS_TRANS_DELAY_FACTOR ; 
 int WPA_DRIVER_FLAGS_HT_2040_COEX ; 
 int /*<<< orphan*/  ap_ht2040_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_iface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_iface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 

void ht40_intolerant_remove(struct hostapd_iface *iface, struct sta_info *sta)
{
	if (!sta->ht40_intolerant_set)
		return;

	sta->ht40_intolerant_set = 0;
	iface->num_sta_ht40_intolerant--;

	if (iface->num_sta_ht40_intolerant == 0 &&
	    (iface->conf->ht_capab & HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET) &&
	    (iface->drv_flags & WPA_DRIVER_FLAGS_HT_2040_COEX)) {
		unsigned int delay_time = OVERLAPPING_BSS_TRANS_DELAY_FACTOR *
			iface->conf->obss_interval;
		wpa_printf(MSG_DEBUG,
			   "HT: Start 20->40 MHz transition timer (%d seconds)",
			   delay_time);
		eloop_cancel_timeout(ap_ht2040_timeout, iface, NULL);
		eloop_register_timeout(delay_time, 0, ap_ht2040_timeout,
				       iface, NULL);
	}
}