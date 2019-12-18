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
struct eap_sim_msg {int dummy; } ;
struct eap_aka_data {unsigned int counter_too_small; unsigned int counter; int /*<<< orphan*/  k_aut; int /*<<< orphan*/  eap_method; scalar_t__ use_result_ind; int /*<<< orphan*/  k_encr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_REAUTHENTICATION ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SIM_AT_COUNTER ; 
 int /*<<< orphan*/  EAP_SIM_AT_COUNTER_TOO_SMALL ; 
 int /*<<< orphan*/  EAP_SIM_AT_ENCR_DATA ; 
 int /*<<< orphan*/  EAP_SIM_AT_IV ; 
 int /*<<< orphan*/  EAP_SIM_AT_MAC ; 
 int /*<<< orphan*/  EAP_SIM_AT_PADDING ; 
 int /*<<< orphan*/  EAP_SIM_AT_RESULT_IND ; 
 int /*<<< orphan*/  EAP_SIM_NONCE_S_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  eap_aka_add_checkcode (struct eap_aka_data*,struct eap_sim_msg*) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sim_msg_add_encr_end (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_encr_start (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_mac (struct eap_sim_msg*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_free (struct eap_sim_msg*) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_aka_response_reauth(struct eap_aka_data *data,
					       u8 id, int counter_too_small,
					       const u8 *nonce_s)
{
	struct eap_sim_msg *msg;
	unsigned int counter;

	wpa_printf(MSG_DEBUG, "Generating EAP-AKA Reauthentication (id=%d)",
		   id);
	msg = eap_sim_msg_init(EAP_CODE_RESPONSE, id, data->eap_method,
			       EAP_AKA_SUBTYPE_REAUTHENTICATION);
	wpa_printf(MSG_DEBUG, "   AT_IV");
	wpa_printf(MSG_DEBUG, "   AT_ENCR_DATA");
	eap_sim_msg_add_encr_start(msg, EAP_SIM_AT_IV, EAP_SIM_AT_ENCR_DATA);

	if (counter_too_small) {
		wpa_printf(MSG_DEBUG, "   *AT_COUNTER_TOO_SMALL");
		eap_sim_msg_add(msg, EAP_SIM_AT_COUNTER_TOO_SMALL, 0, NULL, 0);
		counter = data->counter_too_small;
	} else
		counter = data->counter;

	wpa_printf(MSG_DEBUG, "   *AT_COUNTER %d", counter);
	eap_sim_msg_add(msg, EAP_SIM_AT_COUNTER, counter, NULL, 0);

	if (eap_sim_msg_add_encr_end(msg, data->k_encr, EAP_SIM_AT_PADDING)) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Failed to encrypt "
			   "AT_ENCR_DATA");
		eap_sim_msg_free(msg);
		return NULL;
	}
	eap_aka_add_checkcode(data, msg);
	if (data->use_result_ind) {
		wpa_printf(MSG_DEBUG, "   AT_RESULT_IND");
		eap_sim_msg_add(msg, EAP_SIM_AT_RESULT_IND, 0, NULL, 0);
	}
	wpa_printf(MSG_DEBUG, "   AT_MAC");
	eap_sim_msg_add_mac(msg, EAP_SIM_AT_MAC);
	return eap_sim_msg_finish(msg, data->eap_method, data->k_aut, nonce_s,
				  EAP_SIM_NONCE_S_LEN);
}