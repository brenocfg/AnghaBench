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
typedef  int /*<<< orphan*/  const u8 ;
typedef  scalar_t__ u16 ;
struct eap_sm {int eap_sim_id; int /*<<< orphan*/  eap_sim_db_priv; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_aka_data {scalar_t__ eap_method; scalar_t__ counter; int /*<<< orphan*/  k_encr; int /*<<< orphan*/ * next_reauth_id; int /*<<< orphan*/ * next_pseudonym; } ;

/* Variables and functions */
 scalar_t__ EAP_AKA_MAX_FAST_REAUTHS ; 
 int /*<<< orphan*/  EAP_SIM_AT_COUNTER ; 
 int /*<<< orphan*/  EAP_SIM_AT_ENCR_DATA ; 
 int /*<<< orphan*/  EAP_SIM_AT_IV ; 
 int /*<<< orphan*/  EAP_SIM_AT_NEXT_PSEUDONYM ; 
 int /*<<< orphan*/  EAP_SIM_AT_NEXT_REAUTH_ID ; 
 int /*<<< orphan*/  EAP_SIM_AT_NONCE_S ; 
 int /*<<< orphan*/  EAP_SIM_AT_PADDING ; 
 int /*<<< orphan*/  EAP_SIM_DB_AKA ; 
 int /*<<< orphan*/  EAP_SIM_DB_AKA_PRIME ; 
 scalar_t__ EAP_SIM_NONCE_S_LEN ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/ * eap_sim_db_get_next_pseudonym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * eap_sim_db_get_next_reauth_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ eap_sim_msg_add_encr_end (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_encr_start (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ os_strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_aka_build_encr(struct eap_sm *sm, struct eap_aka_data *data,
			      struct eap_sim_msg *msg, u16 counter,
			      const u8 *nonce_s)
{
	os_free(data->next_pseudonym);
	if (!(sm->eap_sim_id & 0x01)) {
		/* Use of pseudonyms disabled in configuration */
		data->next_pseudonym = NULL;
	} else if (!nonce_s) {
		data->next_pseudonym =
			eap_sim_db_get_next_pseudonym(
				sm->eap_sim_db_priv,
				data->eap_method == EAP_TYPE_AKA_PRIME ?
				EAP_SIM_DB_AKA_PRIME : EAP_SIM_DB_AKA);
	} else {
		/* Do not update pseudonym during re-authentication */
		data->next_pseudonym = NULL;
	}
	os_free(data->next_reauth_id);
	if (!(sm->eap_sim_id & 0x02)) {
		/* Use of fast reauth disabled in configuration */
		data->next_reauth_id = NULL;
	} else if (data->counter <= EAP_AKA_MAX_FAST_REAUTHS) {
		data->next_reauth_id =
			eap_sim_db_get_next_reauth_id(
				sm->eap_sim_db_priv,
				data->eap_method == EAP_TYPE_AKA_PRIME ?
				EAP_SIM_DB_AKA_PRIME : EAP_SIM_DB_AKA);
	} else {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Max fast re-authentication "
			   "count exceeded - force full authentication");
		data->next_reauth_id = NULL;
	}

	if (data->next_pseudonym == NULL && data->next_reauth_id == NULL &&
	    counter == 0 && nonce_s == NULL)
		return 0;

	wpa_printf(MSG_DEBUG, "   AT_IV");
	wpa_printf(MSG_DEBUG, "   AT_ENCR_DATA");
	eap_sim_msg_add_encr_start(msg, EAP_SIM_AT_IV, EAP_SIM_AT_ENCR_DATA);

	if (counter > 0) {
		wpa_printf(MSG_DEBUG, "   *AT_COUNTER (%u)", counter);
		eap_sim_msg_add(msg, EAP_SIM_AT_COUNTER, counter, NULL, 0);
	}

	if (nonce_s) {
		wpa_printf(MSG_DEBUG, "   *AT_NONCE_S");
		eap_sim_msg_add(msg, EAP_SIM_AT_NONCE_S, 0, nonce_s,
				EAP_SIM_NONCE_S_LEN);
	}

	if (data->next_pseudonym) {
		wpa_printf(MSG_DEBUG, "   *AT_NEXT_PSEUDONYM (%s)",
			   data->next_pseudonym);
		eap_sim_msg_add(msg, EAP_SIM_AT_NEXT_PSEUDONYM,
				os_strlen(data->next_pseudonym),
				(u8 *) data->next_pseudonym,
				os_strlen(data->next_pseudonym));
	}

	if (data->next_reauth_id) {
		wpa_printf(MSG_DEBUG, "   *AT_NEXT_REAUTH_ID (%s)",
			   data->next_reauth_id);
		eap_sim_msg_add(msg, EAP_SIM_AT_NEXT_REAUTH_ID,
				os_strlen(data->next_reauth_id),
				(u8 *) data->next_reauth_id,
				os_strlen(data->next_reauth_id));
	}

	if (eap_sim_msg_add_encr_end(msg, data->k_encr, EAP_SIM_AT_PADDING)) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Failed to encrypt "
			   "AT_ENCR_DATA");
		return -1;
	}

	return 0;
}