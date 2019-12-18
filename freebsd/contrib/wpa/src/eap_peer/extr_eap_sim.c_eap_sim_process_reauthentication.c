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
struct eap_sim_data {int reauth; size_t counter; int use_result_ind; scalar_t__ state; int /*<<< orphan*/ * nonce_s; scalar_t__ num_notification; scalar_t__ num_id_req; scalar_t__ result_ind; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; int /*<<< orphan*/  mk; scalar_t__ reauth_id_len; int /*<<< orphan*/ * reauth_id; scalar_t__ last_eap_identity_len; int /*<<< orphan*/ * last_eap_identity; scalar_t__ counter_too_small; int /*<<< orphan*/  k_encr; int /*<<< orphan*/ * reauth_mac; int /*<<< orphan*/  k_aut; } ;
struct eap_sim_attrs {scalar_t__ result_ind; int /*<<< orphan*/ * nonce_s; scalar_t__ counter; int /*<<< orphan*/ * iv; int /*<<< orphan*/  encr_data_len; int /*<<< orphan*/ * encr_data; int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 int CLEAR_EAP_ID ; 
 int CLEAR_REAUTH_ID ; 
 int /*<<< orphan*/  EAP_SIM_MAC_LEN ; 
 size_t EAP_SIM_MAX_FAST_REAUTHS ; 
 int /*<<< orphan*/  EAP_SIM_NONCE_S_LEN ; 
 int /*<<< orphan*/  EAP_SIM_UNABLE_TO_PROCESS_PACKET ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  RESULT_SUCCESS ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  eap_sim_clear_identities (struct eap_sm*,struct eap_sim_data*,int) ; 
 struct wpabuf* eap_sim_client_error (struct eap_sim_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_derive_keys_reauth (size_t,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_learn_ids (struct eap_sm*,struct eap_sim_data*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/ * eap_sim_parse_encr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eap_sim_attrs*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_response_reauth (struct eap_sim_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_sim_state (struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sim_verify_mac (int /*<<< orphan*/ ,struct wpabuf const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_sim_process_reauthentication(
	struct eap_sm *sm, struct eap_sim_data *data, u8 id,
	const struct wpabuf *reqData, struct eap_sim_attrs *attr)
{
	struct eap_sim_attrs eattr;
	u8 *decrypted;

	wpa_printf(MSG_DEBUG, "EAP-SIM: subtype Reauthentication");

	if (data->reauth_id == NULL) {
		wpa_printf(MSG_WARNING, "EAP-SIM: Server is trying "
			   "reauthentication, but no reauth_id available");
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNABLE_TO_PROCESS_PACKET);
	}

	data->reauth = 1;
	if (eap_sim_verify_mac(data->k_aut, reqData, attr->mac, (u8 *) "", 0))
	{
		wpa_printf(MSG_WARNING, "EAP-SIM: Reauthentication "
			   "did not have valid AT_MAC");
#ifdef TEST_FUZZ
		wpa_printf(MSG_INFO,
			   "TEST: Ignore AT_MAC mismatch for fuzz testing");
#else /* TEST_FUZZ */
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNABLE_TO_PROCESS_PACKET);
#endif /* TEST_FUZZ */
	}

	/* At this stage the received MAC has been verified. Use this MAC for
	 * reauth Session-Id calculation if all other checks pass.
	 * The peer does not use the local MAC but the received MAC in deriving
	 * Session-Id. */
#ifdef TEST_FUZZ
	if (attr->mac)
		os_memcpy(data->reauth_mac, attr->mac, EAP_SIM_MAC_LEN);
	else
		os_memset(data->reauth_mac, 0x12, EAP_SIM_MAC_LEN);
#else /* TEST_FUZZ */
	os_memcpy(data->reauth_mac, attr->mac, EAP_SIM_MAC_LEN);
#endif /* TEST_FUZZ */
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: Server MAC",
		    data->reauth_mac, EAP_SIM_MAC_LEN);

	if (attr->encr_data == NULL || attr->iv == NULL) {
		wpa_printf(MSG_WARNING, "EAP-SIM: Reauthentication "
			   "message did not include encrypted data");
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNABLE_TO_PROCESS_PACKET);
	}

	decrypted = eap_sim_parse_encr(data->k_encr, attr->encr_data,
				       attr->encr_data_len, attr->iv, &eattr,
				       0);
	if (decrypted == NULL) {
		wpa_printf(MSG_WARNING, "EAP-SIM: Failed to parse encrypted "
			   "data from reauthentication message");
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNABLE_TO_PROCESS_PACKET);
	}

	if (eattr.nonce_s == NULL || eattr.counter < 0) {
		wpa_printf(MSG_INFO, "EAP-SIM: (encr) No%s%s in reauth packet",
			   !eattr.nonce_s ? " AT_NONCE_S" : "",
			   eattr.counter < 0 ? " AT_COUNTER" : "");
		os_free(decrypted);
		return eap_sim_client_error(data, id,
					    EAP_SIM_UNABLE_TO_PROCESS_PACKET);
	}

	if (eattr.counter < 0 || (size_t) eattr.counter <= data->counter) {
		struct wpabuf *res;
		wpa_printf(MSG_INFO, "EAP-SIM: (encr) Invalid counter "
			   "(%d <= %d)", eattr.counter, data->counter);
		data->counter_too_small = eattr.counter;

		/* Reply using Re-auth w/ AT_COUNTER_TOO_SMALL. The current
		 * reauth_id must not be used to start a new reauthentication.
		 * However, since it was used in the last EAP-Response-Identity
		 * packet, it has to saved for the following fullauth to be
		 * used in MK derivation. */
		os_free(data->last_eap_identity);
		data->last_eap_identity = data->reauth_id;
		data->last_eap_identity_len = data->reauth_id_len;
		data->reauth_id = NULL;
		data->reauth_id_len = 0;

		res = eap_sim_response_reauth(data, id, 1, eattr.nonce_s);
		os_free(decrypted);

		return res;
	}
	data->counter = eattr.counter;

	os_memcpy(data->nonce_s, eattr.nonce_s, EAP_SIM_NONCE_S_LEN);
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: (encr) AT_NONCE_S",
		    data->nonce_s, EAP_SIM_NONCE_S_LEN);

	eap_sim_derive_keys_reauth(data->counter,
				   data->reauth_id, data->reauth_id_len,
				   data->nonce_s, data->mk, data->msk,
				   data->emsk);
	eap_sim_clear_identities(sm, data, CLEAR_REAUTH_ID | CLEAR_EAP_ID);
	eap_sim_learn_ids(sm, data, &eattr);

	if (data->result_ind && attr->result_ind)
		data->use_result_ind = 1;

	if (data->state != FAILURE) {
		eap_sim_state(data, data->use_result_ind ?
			      RESULT_SUCCESS : SUCCESS);
	}

	data->num_id_req = 0;
	data->num_notification = 0;
	if (data->counter > EAP_SIM_MAX_FAST_REAUTHS) {
		wpa_printf(MSG_DEBUG, "EAP-SIM: Maximum number of "
			   "fast reauths performed - force fullauth");
		eap_sim_clear_identities(sm, data,
					 CLEAR_REAUTH_ID | CLEAR_EAP_ID);
	}
	os_free(decrypted);
	return eap_sim_response_reauth(data, id, 0, data->nonce_s);
}