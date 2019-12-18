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
struct wpa_driver_nl80211_data {scalar_t__ ap_scan_as_station; int /*<<< orphan*/  first_bss; scalar_t__ vendor_scan_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_SCAN_RESULTS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 scalar_t__ nl80211_abort_scan (int /*<<< orphan*/ ) ; 
 scalar_t__ nl80211_abort_vendor_scan (struct wpa_driver_nl80211_data*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_driver_nl80211_set_mode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_event (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void wpa_driver_nl80211_scan_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_driver_nl80211_data *drv = eloop_ctx;

	wpa_printf(MSG_DEBUG, "nl80211: Scan timeout - try to abort it");
#ifdef CONFIG_DRIVER_NL80211_QCA
	if (drv->vendor_scan_cookie &&
	    nl80211_abort_vendor_scan(drv, drv->vendor_scan_cookie) == 0)
		return;
#endif /* CONFIG_DRIVER_NL80211_QCA */
	if (!drv->vendor_scan_cookie &&
	    nl80211_abort_scan(drv->first_bss) == 0)
		return;

	wpa_printf(MSG_DEBUG, "nl80211: Failed to abort scan");

	if (drv->ap_scan_as_station != NL80211_IFTYPE_UNSPECIFIED) {
		wpa_driver_nl80211_set_mode(drv->first_bss,
					    drv->ap_scan_as_station);
		drv->ap_scan_as_station = NL80211_IFTYPE_UNSPECIFIED;
	}

	wpa_printf(MSG_DEBUG, "nl80211: Try to get scan results");
	wpa_supplicant_event(timeout_ctx, EVENT_SCAN_RESULTS, NULL);
}