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
struct eap_sm {int dummy; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_aka_data {int reauth; size_t reauth_id_len; size_t pseudonym_len; int /*<<< orphan*/  eap_method; int /*<<< orphan*/ * pseudonym; int /*<<< orphan*/ * reauth_id; } ;
typedef  enum eap_sim_id_req { ____Placeholder_eap_sim_id_req } eap_sim_id_req ;

/* Variables and functions */
 int ANY_ID ; 
 int CLEAR_EAP_ID ; 
 int CLEAR_PSEUDONYM ; 
 int CLEAR_REAUTH_ID ; 
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_IDENTITY ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SIM_AT_IDENTITY ; 
 int FULLAUTH_ID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int NO_ID_REQ ; 
 int /*<<< orphan*/  eap_aka_clear_identities (struct eap_sm*,struct eap_aka_data*,int) ; 
 int /*<<< orphan*/ * eap_get_config_identity (struct eap_sm*,size_t*) ; 
 scalar_t__ eap_sim_anonymous_username (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*,size_t) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_aka_response_identity(struct eap_sm *sm,
						 struct eap_aka_data *data,
						 u8 id,
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
		eap_aka_clear_identities(sm, data, CLEAR_REAUTH_ID);
	} else if (id_req != NO_ID_REQ) {
		identity = eap_get_config_identity(sm, &identity_len);
		if (identity) {
			int ids = CLEAR_PSEUDONYM | CLEAR_REAUTH_ID;

			if (data->pseudonym &&
			    eap_sim_anonymous_username(data->pseudonym,
						       data->pseudonym_len))
				ids &= ~CLEAR_PSEUDONYM;
			eap_aka_clear_identities(sm, data, ids);
		}
	}
	if (id_req != NO_ID_REQ)
		eap_aka_clear_identities(sm, data, CLEAR_EAP_ID);

	wpa_printf(MSG_DEBUG, "Generating EAP-AKA Identity (id=%d)", id);
	msg = eap_sim_msg_init(EAP_CODE_RESPONSE, id, data->eap_method,
			       EAP_AKA_SUBTYPE_IDENTITY);

	if (identity) {
		wpa_hexdump_ascii(MSG_DEBUG, "   AT_IDENTITY",
				  identity, identity_len);
		eap_sim_msg_add(msg, EAP_SIM_AT_IDENTITY, identity_len,
				identity, identity_len);
	}

	return eap_sim_msg_finish(msg, data->eap_method, NULL, NULL, 0);
}