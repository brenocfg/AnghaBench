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
struct wpa_supplicant {struct wpa_ssid* prev_scan_ssid; } ;
struct wpa_ssid {struct wpa_ssid* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* WILDCARD_SSID_SCAN ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_associate (struct wpa_supplicant*,int /*<<< orphan*/ *,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpa_supplicant_req_scan (struct wpa_supplicant*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_network_disabled (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int wpas_temp_disabled (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static void wpa_supplicant_assoc_try(struct wpa_supplicant *wpa_s,
				     struct wpa_ssid *ssid)
{
	int min_temp_disabled = 0;

	while (ssid) {
		if (!wpas_network_disabled(wpa_s, ssid)) {
			int temp_disabled = wpas_temp_disabled(wpa_s, ssid);

			if (temp_disabled <= 0)
				break;

			if (!min_temp_disabled ||
			    temp_disabled < min_temp_disabled)
				min_temp_disabled = temp_disabled;
		}
		ssid = ssid->next;
	}

	/* ap_scan=2 mode - try to associate with each SSID. */
	if (ssid == NULL) {
		wpa_dbg(wpa_s, MSG_DEBUG, "wpa_supplicant_assoc_try: Reached "
			"end of scan list - go back to beginning");
		wpa_s->prev_scan_ssid = WILDCARD_SSID_SCAN;
		wpa_supplicant_req_scan(wpa_s, min_temp_disabled, 0);
		return;
	}
	if (ssid->next) {
		/* Continue from the next SSID on the next attempt. */
		wpa_s->prev_scan_ssid = ssid;
	} else {
		/* Start from the beginning of the SSID list. */
		wpa_s->prev_scan_ssid = WILDCARD_SSID_SCAN;
	}
	wpa_supplicant_associate(wpa_s, NULL, ssid);
}