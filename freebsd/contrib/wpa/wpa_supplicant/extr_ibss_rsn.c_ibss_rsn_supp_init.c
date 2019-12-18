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
struct wpa_sm_ctx {int /*<<< orphan*/  deauthenticate; int /*<<< orphan*/  cancel_auth_timeout; int /*<<< orphan*/  mlme_setprotection; int /*<<< orphan*/  get_network_ctx; int /*<<< orphan*/  set_key; int /*<<< orphan*/  alloc_eapol; int /*<<< orphan*/  get_beacon_ie; int /*<<< orphan*/  ether_send; int /*<<< orphan*/  get_state; int /*<<< orphan*/  set_state; int /*<<< orphan*/  msg_ctx; struct ibss_rsn_peer* ctx; } ;
struct ibss_rsn_peer {int supp_ie_len; int /*<<< orphan*/  addr; int /*<<< orphan*/ * supp; int /*<<< orphan*/  supp_ie; TYPE_1__* ibss_rsn; } ;
struct TYPE_2__ {int /*<<< orphan*/  wpa_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PMK_LEN ; 
 int WPA_CIPHER_CCMP ; 
 int WPA_KEY_MGMT_PSK ; 
 int /*<<< orphan*/  WPA_PARAM_GROUP ; 
 int /*<<< orphan*/  WPA_PARAM_KEY_MGMT ; 
 int /*<<< orphan*/  WPA_PARAM_PAIRWISE ; 
 int /*<<< orphan*/  WPA_PARAM_PROTO ; 
 int /*<<< orphan*/  WPA_PARAM_RSN_ENABLED ; 
 int WPA_PROTO_RSN ; 
 int /*<<< orphan*/  os_free (struct wpa_sm_ctx*) ; 
 struct wpa_sm_ctx* os_zalloc (int) ; 
 int /*<<< orphan*/  supp_alloc_eapol ; 
 int /*<<< orphan*/  supp_cancel_auth_timeout ; 
 int /*<<< orphan*/  supp_deauthenticate ; 
 int /*<<< orphan*/  supp_ether_send ; 
 int /*<<< orphan*/  supp_get_beacon_ie ; 
 int /*<<< orphan*/  supp_get_network_ctx ; 
 int /*<<< orphan*/  supp_get_state ; 
 int /*<<< orphan*/  supp_mlme_setprotection ; 
 int /*<<< orphan*/  supp_set_key ; 
 int /*<<< orphan*/  supp_set_state ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpa_sm_init (struct wpa_sm_ctx*) ; 
 int /*<<< orphan*/  wpa_sm_notify_assoc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_sm_set_assoc_wpa_ie_default (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wpa_sm_set_own_addr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_sm_set_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_sm_set_pmk (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibss_rsn_supp_init(struct ibss_rsn_peer *peer, const u8 *own_addr,
			      const u8 *psk)
{
	struct wpa_sm_ctx *ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL)
		return -1;

	ctx->ctx = peer;
	ctx->msg_ctx = peer->ibss_rsn->wpa_s;
	ctx->set_state = supp_set_state;
	ctx->get_state = supp_get_state;
	ctx->ether_send = supp_ether_send;
	ctx->get_beacon_ie = supp_get_beacon_ie;
	ctx->alloc_eapol = supp_alloc_eapol;
	ctx->set_key = supp_set_key;
	ctx->get_network_ctx = supp_get_network_ctx;
	ctx->mlme_setprotection = supp_mlme_setprotection;
	ctx->cancel_auth_timeout = supp_cancel_auth_timeout;
	ctx->deauthenticate = supp_deauthenticate;
	peer->supp = wpa_sm_init(ctx);
	if (peer->supp == NULL) {
		wpa_printf(MSG_DEBUG, "SUPP: wpa_sm_init() failed");
		os_free(ctx);
		return -1;
	}

	wpa_sm_set_own_addr(peer->supp, own_addr);
	wpa_sm_set_param(peer->supp, WPA_PARAM_RSN_ENABLED, 1);
	wpa_sm_set_param(peer->supp, WPA_PARAM_PROTO, WPA_PROTO_RSN);
	wpa_sm_set_param(peer->supp, WPA_PARAM_PAIRWISE, WPA_CIPHER_CCMP);
	wpa_sm_set_param(peer->supp, WPA_PARAM_GROUP, WPA_CIPHER_CCMP);
	wpa_sm_set_param(peer->supp, WPA_PARAM_KEY_MGMT, WPA_KEY_MGMT_PSK);
	wpa_sm_set_pmk(peer->supp, psk, PMK_LEN, NULL, NULL);

	peer->supp_ie_len = sizeof(peer->supp_ie);
	if (wpa_sm_set_assoc_wpa_ie_default(peer->supp, peer->supp_ie,
					    &peer->supp_ie_len) < 0) {
		wpa_printf(MSG_DEBUG, "SUPP: wpa_sm_set_assoc_wpa_ie_default()"
			   " failed");
		return -1;
	}

	wpa_sm_notify_assoc(peer->supp, peer->addr);

	return 0;
}