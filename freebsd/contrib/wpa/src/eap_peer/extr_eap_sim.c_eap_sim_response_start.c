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
typedef  size_t u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_sim_data {int reauth; size_t* reauth_id; size_t reauth_id_len; size_t* pseudonym; size_t pseudonym_len; size_t const* nonce_mt; size_t selected_version; } ;
typedef  enum eap_sim_id_req { ____Placeholder_eap_sim_id_req } eap_sim_id_req ;

/* Variables and functions */
 int ANY_ID ; 
 int CLEAR_EAP_ID ; 
 int CLEAR_PSEUDONYM ; 
 int CLEAR_REAUTH_ID ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SIM_AT_IDENTITY ; 
 int /*<<< orphan*/  EAP_SIM_AT_NONCE_MT ; 
 int /*<<< orphan*/  EAP_SIM_AT_SELECTED_VERSION ; 
 size_t EAP_SIM_NONCE_MT_LEN ; 
 int /*<<< orphan*/  EAP_SIM_SUBTYPE_START ; 
 int /*<<< orphan*/  EAP_TYPE_SIM ; 
 int FULLAUTH_ID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int NO_ID_REQ ; 
 size_t* eap_get_config_identity (struct eap_sm*,size_t*) ; 
 scalar_t__ eap_sim_anonymous_username (size_t*,size_t) ; 
 int /*<<< orphan*/  eap_sim_clear_identities (struct eap_sm*,struct eap_sim_data*,int) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,size_t,size_t const*,size_t) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,size_t const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,size_t const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_sim_response_start(struct eap_sm *sm,
					      struct eap_sim_data *data, u8 id,
					      enum eap_sim_id_req id_req)
{
	const u8 *identity = NULL;
	size_t identity_len = 0;
	struct eap_sim_msg *msg;

	data->reauth = 0;
	if (id_req == ANY_ID && data->reauth_id) {
		identity = data->reauth_id;
		identity_len = data->reauth_id_len;
		data->reauth = 1;
	} else if ((id_req == ANY_ID || id_req == FULLAUTH_ID) &&
		   data->pseudonym &&
		   !eap_sim_anonymous_username(data->pseudonym,
					       data->pseudonym_len)) {
		identity = data->pseudonym;
		identity_len = data->pseudonym_len;
		eap_sim_clear_identities(sm, data, CLEAR_REAUTH_ID);
	} else if (id_req != NO_ID_REQ) {
		identity = eap_get_config_identity(sm, &identity_len);
		if (identity) {
			int ids = CLEAR_PSEUDONYM | CLEAR_REAUTH_ID;

			if (data->pseudonym &&
			    eap_sim_anonymous_username(data->pseudonym,
						       data->pseudonym_len))
				ids &= ~CLEAR_PSEUDONYM;
			eap_sim_clear_identities(sm, data, ids);
		}
	}
	if (id_req != NO_ID_REQ)
		eap_sim_clear_identities(sm, data, CLEAR_EAP_ID);

	wpa_printf(MSG_DEBUG, "Generating EAP-SIM Start (id=%d)", id);
	msg = eap_sim_msg_init(EAP_CODE_RESPONSE, id,
			       EAP_TYPE_SIM, EAP_SIM_SUBTYPE_START);
	if (!data->reauth) {
		wpa_hexdump(MSG_DEBUG, "   AT_NONCE_MT",
			    data->nonce_mt, EAP_SIM_NONCE_MT_LEN);
		eap_sim_msg_add(msg, EAP_SIM_AT_NONCE_MT, 0,
				data->nonce_mt, EAP_SIM_NONCE_MT_LEN);
		wpa_printf(MSG_DEBUG, "   AT_SELECTED_VERSION %d",
			   data->selected_version);
		eap_sim_msg_add(msg, EAP_SIM_AT_SELECTED_VERSION,
				data->selected_version, NULL, 0);
	}

	if (identity) {
		wpa_hexdump_ascii(MSG_DEBUG, "   AT_IDENTITY",
				  identity, identity_len);
		eap_sim_msg_add(msg, EAP_SIM_AT_IDENTITY, identity_len,
				identity, identity_len);
	}

	return eap_sim_msg_finish(msg, EAP_TYPE_SIM, NULL, NULL, 0);
}