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
struct wpabuf {int dummy; } ;
struct eap_sm {int /*<<< orphan*/  eap_sim_db_priv; scalar_t__ eap_sim_aka_result_ind; } ;
struct eap_sim_attrs {int kdf_count; scalar_t__* kdf; int res_len; int res_len_bits; scalar_t__ result_ind; int /*<<< orphan*/ * res; int /*<<< orphan*/ * mac; int /*<<< orphan*/  checkcode_len; scalar_t__ checkcode; } ;
struct eap_aka_data {scalar_t__ eap_method; scalar_t__ kdf; int res_len; int use_result_ind; int /*<<< orphan*/ * next_reauth_id; int /*<<< orphan*/  mk; scalar_t__ counter; int /*<<< orphan*/  permanent; int /*<<< orphan*/  k_re; int /*<<< orphan*/  k_aut; int /*<<< orphan*/  k_encr; int /*<<< orphan*/ * next_pseudonym; void* notification; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 scalar_t__ EAP_AKA_PRIME_KDF ; 
 void* EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH ; 
 void* EAP_SIM_SUCCESS ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  NOTIFICATION ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_aka_verify_checkcode (struct eap_aka_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_aka_verify_mac (struct eap_aka_data*,struct wpabuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_db_add_pseudonym (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_sim_db_add_reauth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_db_add_reauth_prime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_aka_process_challenge(struct eap_sm *sm,
				      struct eap_aka_data *data,
				      struct wpabuf *respData,
				      struct eap_sim_attrs *attr)
{
	wpa_printf(MSG_DEBUG, "EAP-AKA: Processing Challenge");

#ifdef EAP_SERVER_AKA_PRIME
#if 0
	/* KDF negotiation; to be enabled only after more than one KDF is
	 * supported */
	if (data->eap_method == EAP_TYPE_AKA_PRIME &&
	    attr->kdf_count == 1 && attr->mac == NULL) {
		if (attr->kdf[0] != EAP_AKA_PRIME_KDF) {
			wpa_printf(MSG_WARNING, "EAP-AKA': Peer selected "
				   "unknown KDF");
			data->notification =
				EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
			eap_aka_state(data, NOTIFICATION);
			return;
		}

		data->kdf = attr->kdf[0];

		/* Allow negotiation to continue with the selected KDF by
		 * sending another Challenge message */
		wpa_printf(MSG_DEBUG, "EAP-AKA': KDF %d selected", data->kdf);
		return;
	}
#endif
#endif /* EAP_SERVER_AKA_PRIME */

	if (attr->checkcode &&
	    eap_aka_verify_checkcode(data, attr->checkcode,
				     attr->checkcode_len)) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Invalid AT_CHECKCODE in the "
			   "message");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}
	if (attr->mac == NULL ||
	    eap_aka_verify_mac(data, respData, attr->mac, NULL, 0)) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Challenge message "
			   "did not include valid AT_MAC");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	/*
	 * AT_RES is padded, so verify that there is enough room for RES and
	 * that the RES length in bits matches with the expected RES.
	 */
	if (attr->res == NULL || attr->res_len < data->res_len ||
	    attr->res_len_bits != data->res_len * 8 ||
	    os_memcmp_const(attr->res, data->res, data->res_len) != 0) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Challenge message did not "
			   "include valid AT_RES (attr len=%lu, res len=%lu "
			   "bits, expected %lu bits)",
			   (unsigned long) attr->res_len,
			   (unsigned long) attr->res_len_bits,
			   (unsigned long) data->res_len * 8);
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	wpa_printf(MSG_DEBUG, "EAP-AKA: Challenge response includes the "
		   "correct AT_MAC");
	if (sm->eap_sim_aka_result_ind && attr->result_ind) {
		data->use_result_ind = 1;
		data->notification = EAP_SIM_SUCCESS;
		eap_aka_state(data, NOTIFICATION);
	} else
		eap_aka_state(data, SUCCESS);

	if (data->next_pseudonym) {
		eap_sim_db_add_pseudonym(sm->eap_sim_db_priv, data->permanent,
					 data->next_pseudonym);
		data->next_pseudonym = NULL;
	}
	if (data->next_reauth_id) {
		if (data->eap_method == EAP_TYPE_AKA_PRIME) {
#ifdef EAP_SERVER_AKA_PRIME
			eap_sim_db_add_reauth_prime(sm->eap_sim_db_priv,
						    data->permanent,
						    data->next_reauth_id,
						    data->counter + 1,
						    data->k_encr, data->k_aut,
						    data->k_re);
#endif /* EAP_SERVER_AKA_PRIME */
		} else {
			eap_sim_db_add_reauth(sm->eap_sim_db_priv,
					      data->permanent,
					      data->next_reauth_id,
					      data->counter + 1,
					      data->mk);
		}
		data->next_reauth_id = NULL;
	}
}