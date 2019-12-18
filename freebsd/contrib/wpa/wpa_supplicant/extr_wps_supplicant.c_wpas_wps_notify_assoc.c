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
typedef  int /*<<< orphan*/  u8 ;
struct wps_ap_info {int /*<<< orphan*/  last_attempt; int /*<<< orphan*/  tries; } ;
struct wpa_supplicant {int /*<<< orphan*/  wps_ap_iter; scalar_t__ after_wps; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 struct wps_ap_info* wpas_wps_get_ap_info (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 

void wpas_wps_notify_assoc(struct wpa_supplicant *wpa_s, const u8 *bssid)
{
	struct wps_ap_info *ap;

	wpa_s->after_wps = 0;

	if (!wpa_s->wps_ap_iter)
		return;
	ap = wpas_wps_get_ap_info(wpa_s, bssid);
	if (ap == NULL)
		return;
	ap->tries++;
	os_get_reltime(&ap->last_attempt);
}