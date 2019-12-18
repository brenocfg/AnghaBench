#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sta_info {int flags; scalar_t__ auth_alg; TYPE_3__* eapol_sm; int /*<<< orphan*/  addr; int /*<<< orphan*/  wpa_sm; } ;
struct rsn_pmksa_cache_entry {int dummy; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_8__ {void* reAuthenticate; scalar_t__ eap; void* authFail; void* authSuccess; void* be_auth_state; void* auth_pae_state; TYPE_2__* eap_if; void* keyRun; void* portValid; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {void* eapKeyAvailable; void* portEnabled; } ;
struct TYPE_6__ {scalar_t__ wps_state; int /*<<< orphan*/  ieee802_1x; int /*<<< orphan*/  osen; scalar_t__ wpa; } ;

/* Variables and functions */
 void* AUTH_PAE_AUTHENTICATING ; 
 void* BE_AUTH_SUCCESS ; 
 int /*<<< orphan*/  EAPOL_SM_WAIT_START ; 
 void* FALSE ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_INFO ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE8021X ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* TRUE ; 
 scalar_t__ WLAN_AUTH_FILS_PK ; 
 scalar_t__ WLAN_AUTH_FILS_SK ; 
 scalar_t__ WLAN_AUTH_FILS_SK_PFS ; 
 scalar_t__ WLAN_AUTH_FT ; 
 int WLAN_STA_MAYBE_WPS ; 
 int WLAN_STA_WPS ; 
 int WLAN_STA_WPS2 ; 
 int WPA_KEY_MGMT_DPP ; 
 int WPA_KEY_MGMT_OWE ; 
 int /*<<< orphan*/  ap_sta_bind_vlan (struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  eap_sm_notify_cached (scalar_t__) ; 
 int /*<<< orphan*/  eapol_auth_step (TYPE_3__*) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* ieee802_1x_alloc_eapol_sm (struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  ieee802_1x_free_station (struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  pmksa_cache_to_eapol_data (struct hostapd_data*,struct rsn_pmksa_cache_entry*,TYPE_3__*) ; 
 int /*<<< orphan*/  wpa_auth_set_ptk_rekey_timer (int /*<<< orphan*/ ) ; 
 struct rsn_pmksa_cache_entry* wpa_auth_sta_get_pmksa (int /*<<< orphan*/ ) ; 
 int wpa_auth_sta_key_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_wpa_psk (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void ieee802_1x_new_station(struct hostapd_data *hapd, struct sta_info *sta)
{
	struct rsn_pmksa_cache_entry *pmksa;
	int reassoc = 1;
	int force_1x = 0;
	int key_mgmt;

#ifdef CONFIG_WPS
	if (hapd->conf->wps_state &&
	    ((hapd->conf->wpa && (sta->flags & WLAN_STA_MAYBE_WPS)) ||
	     (sta->flags & WLAN_STA_WPS))) {
		/*
		 * Need to enable IEEE 802.1X/EAPOL state machines for possible
		 * WPS handshake even if IEEE 802.1X/EAPOL is not used for
		 * authentication in this BSS.
		 */
		force_1x = 1;
	}
#endif /* CONFIG_WPS */

	if (!force_1x && !hapd->conf->ieee802_1x && !hapd->conf->osen) {
		wpa_printf(MSG_DEBUG, "IEEE 802.1X: Ignore STA - "
			   "802.1X not enabled or forced for WPS");
		/*
		 * Clear any possible EAPOL authenticator state to support
		 * reassociation change from WPS to PSK.
		 */
		ieee802_1x_free_station(hapd, sta);
		return;
	}

	key_mgmt = wpa_auth_sta_key_mgmt(sta->wpa_sm);
	if (key_mgmt != -1 &&
	    (wpa_key_mgmt_wpa_psk(key_mgmt) || key_mgmt == WPA_KEY_MGMT_OWE ||
	     key_mgmt == WPA_KEY_MGMT_DPP)) {
		wpa_printf(MSG_DEBUG, "IEEE 802.1X: Ignore STA - using PSK");
		/*
		 * Clear any possible EAPOL authenticator state to support
		 * reassociation change from WPA-EAP to PSK.
		 */
		ieee802_1x_free_station(hapd, sta);
		return;
	}

	if (sta->eapol_sm == NULL) {
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_DEBUG, "start authentication");
		sta->eapol_sm = ieee802_1x_alloc_eapol_sm(hapd, sta);
		if (sta->eapol_sm == NULL) {
			hostapd_logger(hapd, sta->addr,
				       HOSTAPD_MODULE_IEEE8021X,
				       HOSTAPD_LEVEL_INFO,
				       "failed to allocate state machine");
			return;
		}
		reassoc = 0;
	}

#ifdef CONFIG_WPS
	sta->eapol_sm->flags &= ~EAPOL_SM_WAIT_START;
	if (!hapd->conf->ieee802_1x && hapd->conf->wps_state &&
	    !(sta->flags & WLAN_STA_WPS2)) {
		/*
		 * Delay EAPOL frame transmission until a possible WPS STA
		 * initiates the handshake with EAPOL-Start. Only allow the
		 * wait to be skipped if the STA is known to support WPS 2.0.
		 */
		wpa_printf(MSG_DEBUG, "WPS: Do not start EAPOL until "
			   "EAPOL-Start is received");
		sta->eapol_sm->flags |= EAPOL_SM_WAIT_START;
	}
#endif /* CONFIG_WPS */

	sta->eapol_sm->eap_if->portEnabled = TRUE;

#ifdef CONFIG_IEEE80211R_AP
	if (sta->auth_alg == WLAN_AUTH_FT) {
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_DEBUG,
			       "PMK from FT - skip IEEE 802.1X/EAP");
		/* Setup EAPOL state machines to already authenticated state
		 * because of existing FT information from R0KH. */
		sta->eapol_sm->keyRun = TRUE;
		sta->eapol_sm->eap_if->eapKeyAvailable = TRUE;
		sta->eapol_sm->auth_pae_state = AUTH_PAE_AUTHENTICATING;
		sta->eapol_sm->be_auth_state = BE_AUTH_SUCCESS;
		sta->eapol_sm->authSuccess = TRUE;
		sta->eapol_sm->authFail = FALSE;
		sta->eapol_sm->portValid = TRUE;
		if (sta->eapol_sm->eap)
			eap_sm_notify_cached(sta->eapol_sm->eap);
		ap_sta_bind_vlan(hapd, sta);
		return;
	}
#endif /* CONFIG_IEEE80211R_AP */

#ifdef CONFIG_FILS
	if (sta->auth_alg == WLAN_AUTH_FILS_SK ||
	    sta->auth_alg == WLAN_AUTH_FILS_SK_PFS ||
	    sta->auth_alg == WLAN_AUTH_FILS_PK) {
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_DEBUG,
			       "PMK from FILS - skip IEEE 802.1X/EAP");
		/* Setup EAPOL state machines to already authenticated state
		 * because of existing FILS information. */
		sta->eapol_sm->keyRun = TRUE;
		sta->eapol_sm->eap_if->eapKeyAvailable = TRUE;
		sta->eapol_sm->auth_pae_state = AUTH_PAE_AUTHENTICATING;
		sta->eapol_sm->be_auth_state = BE_AUTH_SUCCESS;
		sta->eapol_sm->authSuccess = TRUE;
		sta->eapol_sm->authFail = FALSE;
		sta->eapol_sm->portValid = TRUE;
		if (sta->eapol_sm->eap)
			eap_sm_notify_cached(sta->eapol_sm->eap);
		wpa_auth_set_ptk_rekey_timer(sta->wpa_sm);
		return;
	}
#endif /* CONFIG_FILS */

	pmksa = wpa_auth_sta_get_pmksa(sta->wpa_sm);
	if (pmksa) {
		hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
			       HOSTAPD_LEVEL_DEBUG,
			       "PMK from PMKSA cache - skip IEEE 802.1X/EAP");
		/* Setup EAPOL state machines to already authenticated state
		 * because of existing PMKSA information in the cache. */
		sta->eapol_sm->keyRun = TRUE;
		sta->eapol_sm->eap_if->eapKeyAvailable = TRUE;
		sta->eapol_sm->auth_pae_state = AUTH_PAE_AUTHENTICATING;
		sta->eapol_sm->be_auth_state = BE_AUTH_SUCCESS;
		sta->eapol_sm->authSuccess = TRUE;
		sta->eapol_sm->authFail = FALSE;
		if (sta->eapol_sm->eap)
			eap_sm_notify_cached(sta->eapol_sm->eap);
		pmksa_cache_to_eapol_data(hapd, pmksa, sta->eapol_sm);
		ap_sta_bind_vlan(hapd, sta);
	} else {
		if (reassoc) {
			/*
			 * Force EAPOL state machines to start
			 * re-authentication without having to wait for the
			 * Supplicant to send EAPOL-Start.
			 */
			sta->eapol_sm->reAuthenticate = TRUE;
		}
		eapol_auth_step(sta->eapol_sm);
	}
}