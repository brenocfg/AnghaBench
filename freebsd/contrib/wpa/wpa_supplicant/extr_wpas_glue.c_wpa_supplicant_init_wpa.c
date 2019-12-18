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
struct wpa_supplicant {int /*<<< orphan*/ * wpa; } ;
struct wpa_sm_ctx {int /*<<< orphan*/  channel_info; int /*<<< orphan*/  fils_hlp_rx; int /*<<< orphan*/  key_mgmt_set_pmk; int /*<<< orphan*/  set_rekey_offload; int /*<<< orphan*/  tdls_disable_channel_switch; int /*<<< orphan*/  tdls_enable_channel_switch; int /*<<< orphan*/  tdls_peer_addset; int /*<<< orphan*/  tdls_oper; int /*<<< orphan*/  send_tdls_mgmt; int /*<<< orphan*/  tdls_get_capa; int /*<<< orphan*/  mark_authenticated; int /*<<< orphan*/  send_ft_action; int /*<<< orphan*/  update_ft_ies; int /*<<< orphan*/  mlme_setprotection; int /*<<< orphan*/  get_config_blob; int /*<<< orphan*/  set_config_blob; int /*<<< orphan*/  remove_pmkid; int /*<<< orphan*/  add_pmkid; int /*<<< orphan*/  cancel_auth_timeout; int /*<<< orphan*/  alloc_eapol; int /*<<< orphan*/  get_beacon_ie; int /*<<< orphan*/  ether_send; int /*<<< orphan*/  get_bssid; int /*<<< orphan*/  get_network_ctx; int /*<<< orphan*/  set_key; int /*<<< orphan*/  deauthenticate; int /*<<< orphan*/  get_state; int /*<<< orphan*/  set_state; struct wpa_supplicant* msg_ctx; struct wpa_supplicant* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  _wpa_alloc_eapol ; 
 int /*<<< orphan*/  _wpa_ether_send ; 
 int /*<<< orphan*/  _wpa_supplicant_cancel_auth_timeout ; 
 int /*<<< orphan*/  _wpa_supplicant_deauthenticate ; 
 int /*<<< orphan*/  _wpa_supplicant_get_state ; 
 int /*<<< orphan*/  _wpa_supplicant_set_state ; 
 int /*<<< orphan*/  os_free (struct wpa_sm_ctx*) ; 
 struct wpa_sm_ctx* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpa_sm_init (struct wpa_sm_ctx*) ; 
 int /*<<< orphan*/  wpa_supplicant_add_pmkid ; 
 int /*<<< orphan*/  wpa_supplicant_channel_info ; 
 int /*<<< orphan*/  wpa_supplicant_fils_hlp_rx ; 
 int /*<<< orphan*/  wpa_supplicant_get_beacon_ie ; 
 int /*<<< orphan*/  wpa_supplicant_get_bssid ; 
 int /*<<< orphan*/  wpa_supplicant_get_config_blob ; 
 int /*<<< orphan*/  wpa_supplicant_get_network_ctx ; 
 int /*<<< orphan*/  wpa_supplicant_key_mgmt_set_pmk ; 
 int /*<<< orphan*/  wpa_supplicant_mark_authenticated ; 
 int /*<<< orphan*/  wpa_supplicant_mlme_setprotection ; 
 int /*<<< orphan*/  wpa_supplicant_remove_pmkid ; 
 int /*<<< orphan*/  wpa_supplicant_send_ft_action ; 
 int /*<<< orphan*/  wpa_supplicant_send_tdls_mgmt ; 
 int /*<<< orphan*/  wpa_supplicant_set_config_blob ; 
 int /*<<< orphan*/  wpa_supplicant_set_key ; 
 int /*<<< orphan*/  wpa_supplicant_set_rekey_offload ; 
 int /*<<< orphan*/  wpa_supplicant_tdls_disable_channel_switch ; 
 int /*<<< orphan*/  wpa_supplicant_tdls_enable_channel_switch ; 
 int /*<<< orphan*/  wpa_supplicant_tdls_get_capa ; 
 int /*<<< orphan*/  wpa_supplicant_tdls_oper ; 
 int /*<<< orphan*/  wpa_supplicant_tdls_peer_addset ; 
 int /*<<< orphan*/  wpa_supplicant_update_ft_ies ; 

int wpa_supplicant_init_wpa(struct wpa_supplicant *wpa_s)
{
#ifndef CONFIG_NO_WPA
	struct wpa_sm_ctx *ctx;
	ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL) {
		wpa_printf(MSG_ERROR, "Failed to allocate WPA context.");
		return -1;
	}

	ctx->ctx = wpa_s;
	ctx->msg_ctx = wpa_s;
	ctx->set_state = _wpa_supplicant_set_state;
	ctx->get_state = _wpa_supplicant_get_state;
	ctx->deauthenticate = _wpa_supplicant_deauthenticate;
	ctx->set_key = wpa_supplicant_set_key;
	ctx->get_network_ctx = wpa_supplicant_get_network_ctx;
	ctx->get_bssid = wpa_supplicant_get_bssid;
	ctx->ether_send = _wpa_ether_send;
	ctx->get_beacon_ie = wpa_supplicant_get_beacon_ie;
	ctx->alloc_eapol = _wpa_alloc_eapol;
	ctx->cancel_auth_timeout = _wpa_supplicant_cancel_auth_timeout;
	ctx->add_pmkid = wpa_supplicant_add_pmkid;
	ctx->remove_pmkid = wpa_supplicant_remove_pmkid;
#ifndef CONFIG_NO_CONFIG_BLOBS
	ctx->set_config_blob = wpa_supplicant_set_config_blob;
	ctx->get_config_blob = wpa_supplicant_get_config_blob;
#endif /* CONFIG_NO_CONFIG_BLOBS */
	ctx->mlme_setprotection = wpa_supplicant_mlme_setprotection;
#ifdef CONFIG_IEEE80211R
	ctx->update_ft_ies = wpa_supplicant_update_ft_ies;
	ctx->send_ft_action = wpa_supplicant_send_ft_action;
	ctx->mark_authenticated = wpa_supplicant_mark_authenticated;
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_TDLS
	ctx->tdls_get_capa = wpa_supplicant_tdls_get_capa;
	ctx->send_tdls_mgmt = wpa_supplicant_send_tdls_mgmt;
	ctx->tdls_oper = wpa_supplicant_tdls_oper;
	ctx->tdls_peer_addset = wpa_supplicant_tdls_peer_addset;
	ctx->tdls_enable_channel_switch =
		wpa_supplicant_tdls_enable_channel_switch;
	ctx->tdls_disable_channel_switch =
		wpa_supplicant_tdls_disable_channel_switch;
#endif /* CONFIG_TDLS */
	ctx->set_rekey_offload = wpa_supplicant_set_rekey_offload;
	ctx->key_mgmt_set_pmk = wpa_supplicant_key_mgmt_set_pmk;
	ctx->fils_hlp_rx = wpa_supplicant_fils_hlp_rx;
	ctx->channel_info = wpa_supplicant_channel_info;

	wpa_s->wpa = wpa_sm_init(ctx);
	if (wpa_s->wpa == NULL) {
		wpa_printf(MSG_ERROR, "Failed to initialize WPA state "
			   "machine");
		os_free(ctx);
		return -1;
	}
#endif /* CONFIG_NO_WPA */

	return 0;
}