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
struct wpabuf {int dummy; } ;
struct eap_sm {scalar_t__ eap_sim_aka_result_ind; int /*<<< orphan*/  identity_len; int /*<<< orphan*/  identity; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_aka_data {int /*<<< orphan*/  reauth_mac; int /*<<< orphan*/  k_aut; int /*<<< orphan*/  eap_method; int /*<<< orphan*/  nonce_s; int /*<<< orphan*/  counter; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; int /*<<< orphan*/  mk; int /*<<< orphan*/  k_encr; int /*<<< orphan*/  k_re; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_REAUTHENTICATION ; 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_SIM_AT_MAC ; 
 int /*<<< orphan*/  EAP_SIM_AT_RESULT_IND ; 
 scalar_t__ EAP_SIM_MAC_LEN ; 
 int /*<<< orphan*/  EAP_SIM_NONCE_S_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  eap_aka_add_checkcode (struct eap_aka_data*,struct eap_sim_msg*) ; 
 scalar_t__ eap_aka_build_encr (struct eap_sm*,struct eap_aka_data*,struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_aka_prime_derive_keys_reauth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_derive_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_derive_keys_reauth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_mac (struct eap_sim_msg*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_free (struct eap_sim_msg*) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpabuf_head_u8 (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static struct wpabuf * eap_aka_build_reauth(struct eap_sm *sm,
					    struct eap_aka_data *data, u8 id)
{
	struct eap_sim_msg *msg;
	struct wpabuf *buf;

	wpa_printf(MSG_DEBUG, "EAP-AKA: Generating Re-authentication");

	if (random_get_bytes(data->nonce_s, EAP_SIM_NONCE_S_LEN))
		return NULL;
	wpa_hexdump_key(MSG_MSGDUMP, "EAP-AKA: NONCE_S",
			data->nonce_s, EAP_SIM_NONCE_S_LEN);

	if (data->eap_method == EAP_TYPE_AKA_PRIME) {
		eap_aka_prime_derive_keys_reauth(data->k_re, data->counter,
						 sm->identity,
						 sm->identity_len,
						 data->nonce_s,
						 data->msk, data->emsk);
	} else {
		eap_sim_derive_keys(data->mk, data->k_encr, data->k_aut,
				    data->msk, data->emsk);
		eap_sim_derive_keys_reauth(data->counter, sm->identity,
					   sm->identity_len, data->nonce_s,
					   data->mk, data->msk, data->emsk);
	}

	msg = eap_sim_msg_init(EAP_CODE_REQUEST, id, data->eap_method,
			       EAP_AKA_SUBTYPE_REAUTHENTICATION);

	if (eap_aka_build_encr(sm, data, msg, data->counter, data->nonce_s)) {
		eap_sim_msg_free(msg);
		return NULL;
	}

	eap_aka_add_checkcode(data, msg);

	if (sm->eap_sim_aka_result_ind) {
		wpa_printf(MSG_DEBUG, "   AT_RESULT_IND");
		eap_sim_msg_add(msg, EAP_SIM_AT_RESULT_IND, 0, NULL, 0);
	}

	wpa_printf(MSG_DEBUG, "   AT_MAC");
	eap_sim_msg_add_mac(msg, EAP_SIM_AT_MAC);
	buf = eap_sim_msg_finish(msg, data->eap_method, data->k_aut, NULL, 0);

	/* Remember this MAC before sending it to the peer. This MAC is used for
	 * Session-Id calculation after receiving response from the peer and
	 * after all other checks pass. */
	os_memcpy(data->reauth_mac,
		  wpabuf_head_u8(buf) + wpabuf_len(buf) - EAP_SIM_MAC_LEN,
		  EAP_SIM_MAC_LEN);

	return buf;
}