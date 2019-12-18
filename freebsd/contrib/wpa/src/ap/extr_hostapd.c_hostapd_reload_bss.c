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
typedef  int /*<<< orphan*/  const u8 ;
struct hostapd_ssid {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; scalar_t__ ssid_set; TYPE_3__* wpa_psk; scalar_t__ wpa_passphrase; scalar_t__ wpa_passphrase_set; int /*<<< orphan*/  wpa_psk_set; } ;
struct hostapd_data {TYPE_2__* conf; int /*<<< orphan*/ * wpa_auth; int /*<<< orphan*/  radius; TYPE_1__* iconf; int /*<<< orphan*/  started; } ;
struct TYPE_6__ {int /*<<< orphan*/  next; } ;
struct TYPE_5__ {scalar_t__ wmm_enabled; int /*<<< orphan*/  iface; struct hostapd_ssid ssid; scalar_t__ wpa; scalar_t__ osen; scalar_t__ ieee802_1x; int /*<<< orphan*/  radius; } ;
struct TYPE_4__ {scalar_t__ ieee80211n; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  hostapd_config_clear_wpa_psk (TYPE_3__**) ; 
 int /*<<< orphan*/  hostapd_reconfig_wpa (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_set_drv_ieee8021x (struct hostapd_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hostapd_set_generic_elem (struct hostapd_data*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  hostapd_set_privacy (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ hostapd_set_ssid (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_setup_encryption (int /*<<< orphan*/ ,struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_setup_wpa (struct hostapd_data*) ; 
 scalar_t__ hostapd_setup_wpa_psk (TYPE_2__*) ; 
 int /*<<< orphan*/  hostapd_update_wps (struct hostapd_data*) ; 
 int /*<<< orphan*/  ieee802_11_set_beacon (struct hostapd_data*) ; 
 int /*<<< orphan*/  radius_client_reconfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* wpa_auth_get_wpa_ie (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  wpa_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_init_keys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void hostapd_reload_bss(struct hostapd_data *hapd)
{
	struct hostapd_ssid *ssid;

	if (!hapd->started)
		return;

	if (hapd->conf->wmm_enabled < 0)
		hapd->conf->wmm_enabled = hapd->iconf->ieee80211n;

#ifndef CONFIG_NO_RADIUS
	radius_client_reconfig(hapd->radius, hapd->conf->radius);
#endif /* CONFIG_NO_RADIUS */

	ssid = &hapd->conf->ssid;
	if (!ssid->wpa_psk_set && ssid->wpa_psk && !ssid->wpa_psk->next &&
	    ssid->wpa_passphrase_set && ssid->wpa_passphrase) {
		/*
		 * Force PSK to be derived again since SSID or passphrase may
		 * have changed.
		 */
		hostapd_config_clear_wpa_psk(&hapd->conf->ssid.wpa_psk);
	}
	if (hostapd_setup_wpa_psk(hapd->conf)) {
		wpa_printf(MSG_ERROR, "Failed to re-configure WPA PSK "
			   "after reloading configuration");
	}

	if (hapd->conf->ieee802_1x || hapd->conf->wpa)
		hostapd_set_drv_ieee8021x(hapd, hapd->conf->iface, 1);
	else
		hostapd_set_drv_ieee8021x(hapd, hapd->conf->iface, 0);

	if ((hapd->conf->wpa || hapd->conf->osen) && hapd->wpa_auth == NULL) {
		hostapd_setup_wpa(hapd);
		if (hapd->wpa_auth)
			wpa_init_keys(hapd->wpa_auth);
	} else if (hapd->conf->wpa) {
		const u8 *wpa_ie;
		size_t wpa_ie_len;
		hostapd_reconfig_wpa(hapd);
		wpa_ie = wpa_auth_get_wpa_ie(hapd->wpa_auth, &wpa_ie_len);
		if (hostapd_set_generic_elem(hapd, wpa_ie, wpa_ie_len))
			wpa_printf(MSG_ERROR, "Failed to configure WPA IE for "
				   "the kernel driver.");
	} else if (hapd->wpa_auth) {
		wpa_deinit(hapd->wpa_auth);
		hapd->wpa_auth = NULL;
		hostapd_set_privacy(hapd, 0);
		hostapd_setup_encryption(hapd->conf->iface, hapd);
		hostapd_set_generic_elem(hapd, (u8 *) "", 0);
	}

	ieee802_11_set_beacon(hapd);
	hostapd_update_wps(hapd);

	if (hapd->conf->ssid.ssid_set &&
	    hostapd_set_ssid(hapd, hapd->conf->ssid.ssid,
			     hapd->conf->ssid.ssid_len)) {
		wpa_printf(MSG_ERROR, "Could not set SSID for kernel driver");
		/* try to continue */
	}
	wpa_printf(MSG_DEBUG, "Reconfigured interface %s", hapd->conf->iface);
}