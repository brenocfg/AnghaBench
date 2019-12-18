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
struct hostapd_data {TYPE_1__* wps; struct hostapd_data* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  upnp_msgs; int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_free_wps (TYPE_1__*) ; 
 int /*<<< orphan*/  hostapd_wps_ap_pin_timeout ; 
 int /*<<< orphan*/  hostapd_wps_clear_ies (struct hostapd_data*,int) ; 
 int /*<<< orphan*/  hostapd_wps_reenable_ap_pin ; 
 int /*<<< orphan*/  hostapd_wps_upnp_deinit (struct hostapd_data*) ; 
 int /*<<< orphan*/  wps_free_pending_msgs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_registrar_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_reload_config ; 

void hostapd_deinit_wps(struct hostapd_data *hapd)
{
	eloop_cancel_timeout(hostapd_wps_reenable_ap_pin, hapd, NULL);
	eloop_cancel_timeout(hostapd_wps_ap_pin_timeout, hapd, NULL);
	eloop_cancel_timeout(wps_reload_config, hapd->iface, NULL);
	if (hapd->wps == NULL) {
		hostapd_wps_clear_ies(hapd, 1);
		return;
	}
#ifdef CONFIG_WPS_UPNP
	hostapd_wps_upnp_deinit(hapd);
#endif /* CONFIG_WPS_UPNP */
	wps_registrar_deinit(hapd->wps->registrar);
	wps_free_pending_msgs(hapd->wps->upnp_msgs);
	hostapd_free_wps(hapd->wps);
	hapd->wps = NULL;
	hostapd_wps_clear_ies(hapd, 1);
}