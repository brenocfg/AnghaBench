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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {int /*<<< orphan*/ * l2; TYPE_1__* conf; scalar_t__ drv_priv; int /*<<< orphan*/ * wpa_auth; } ;
struct TYPE_2__ {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELOOP_ALL_CTX ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/  (*) (struct hostapd_data*,int /*<<< orphan*/ *),struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_oui_deliver_later (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ hostapd_set_generic_elem (struct hostapd_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hostapd_set_privacy (struct hostapd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_wpa_ft_rrb_rx_later (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_wpa_unregister_ft_oui (struct hostapd_data*) ; 
 int /*<<< orphan*/  ieee80211_tkip_countermeasures_deinit (struct hostapd_data*) ; 
 int /*<<< orphan*/  ieee802_1x_deinit (struct hostapd_data*) ; 
 int /*<<< orphan*/  l2_packet_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsn_preauth_iface_deinit (struct hostapd_data*) ; 
 int /*<<< orphan*/  wpa_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void hostapd_deinit_wpa(struct hostapd_data *hapd)
{
	ieee80211_tkip_countermeasures_deinit(hapd);
	rsn_preauth_iface_deinit(hapd);
	if (hapd->wpa_auth) {
		wpa_deinit(hapd->wpa_auth);
		hapd->wpa_auth = NULL;

		if (hapd->drv_priv && hostapd_set_privacy(hapd, 0)) {
			wpa_printf(MSG_DEBUG, "Could not disable "
				   "PrivacyInvoked for interface %s",
				   hapd->conf->iface);
		}

		if (hapd->drv_priv &&
		    hostapd_set_generic_elem(hapd, (u8 *) "", 0)) {
			wpa_printf(MSG_DEBUG, "Could not remove generic "
				   "information element from interface %s",
				   hapd->conf->iface);
		}
	}
	ieee802_1x_deinit(hapd);

#ifdef CONFIG_IEEE80211R_AP
	eloop_cancel_timeout(hostapd_wpa_ft_rrb_rx_later, hapd, ELOOP_ALL_CTX);
	hostapd_wpa_ft_rrb_rx_later(hapd, NULL); /* flush without delivering */
	eloop_cancel_timeout(hostapd_oui_deliver_later, hapd, ELOOP_ALL_CTX);
	hostapd_oui_deliver_later(hapd, NULL); /* flush without delivering */
	l2_packet_deinit(hapd->l2);
	hapd->l2 = NULL;
	hostapd_wpa_unregister_ft_oui(hapd);
#endif /* CONFIG_IEEE80211R_AP */
}