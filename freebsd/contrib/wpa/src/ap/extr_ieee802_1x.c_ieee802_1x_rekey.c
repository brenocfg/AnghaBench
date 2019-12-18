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
struct hostapd_data {TYPE_1__* conf; struct eapol_authenticator* eapol_auth; } ;
struct eapol_authenticator {int default_wep_key_idx; int /*<<< orphan*/ * default_wep_key; } ;
struct TYPE_2__ {scalar_t__ individual_wep_key_len; scalar_t__ wep_rekeying_period; int /*<<< orphan*/  default_wep_key_len; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_WARNING ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE8021X ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_ALG_WEP ; 
 int /*<<< orphan*/  ap_for_each_sta (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  broadcast_ether_addr ; 
 int /*<<< orphan*/  eloop_register_timeout (scalar_t__,int /*<<< orphan*/ ,void (*) (void*,void*),struct hostapd_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ hostapd_drv_set_key (int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ieee802_1x_rekey_broadcast (struct hostapd_data*) ; 
 int /*<<< orphan*/  ieee802_1x_sta_key_available ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ieee802_1x_rekey(void *eloop_ctx, void *timeout_ctx)
{
	struct hostapd_data *hapd = eloop_ctx;
	struct eapol_authenticator *eapol = hapd->eapol_auth;

	if (eapol->default_wep_key_idx >= 3)
		eapol->default_wep_key_idx =
			hapd->conf->individual_wep_key_len > 0 ? 1 : 0;
	else
		eapol->default_wep_key_idx++;

	wpa_printf(MSG_DEBUG, "IEEE 802.1X: New default WEP key index %d",
		   eapol->default_wep_key_idx);

	if (ieee802_1x_rekey_broadcast(hapd)) {
		hostapd_logger(hapd, NULL, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_WARNING, "failed to generate a "
			       "new broadcast key");
		os_free(eapol->default_wep_key);
		eapol->default_wep_key = NULL;
		return;
	}

	/* TODO: Could setup key for RX here, but change default TX keyid only
	 * after new broadcast key has been sent to all stations. */
	if (hostapd_drv_set_key(hapd->conf->iface, hapd, WPA_ALG_WEP,
				broadcast_ether_addr,
				eapol->default_wep_key_idx, 1, NULL, 0,
				eapol->default_wep_key,
				hapd->conf->default_wep_key_len)) {
		hostapd_logger(hapd, NULL, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_WARNING, "failed to configure a "
			       "new broadcast key");
		os_free(eapol->default_wep_key);
		eapol->default_wep_key = NULL;
		return;
	}

	ap_for_each_sta(hapd, ieee802_1x_sta_key_available, NULL);

	if (hapd->conf->wep_rekeying_period > 0) {
		eloop_register_timeout(hapd->conf->wep_rekeying_period, 0,
				       ieee802_1x_rekey, hapd, NULL);
	}
}