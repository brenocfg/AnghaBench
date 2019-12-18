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
struct hostapd_data {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int eloop_deplete_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_reload_config ; 

void hostapd_wps_eap_completed(struct hostapd_data *hapd)
{
	/*
	 * Reduce race condition of the station trying to reconnect immediately
	 * after AP reconfiguration through WPS by rescheduling the reload
	 * timeout to happen after EAP completion rather than the originally
	 * scheduled 100 ms after new configuration became known.
	 */
	if (eloop_deplete_timeout(0, 0, wps_reload_config, hapd->iface, NULL) ==
	    1)
		wpa_printf(MSG_DEBUG, "WPS: Reschedule immediate configuration reload");
}