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
struct eap_sm {scalar_t__ eap_sim_aka_result_ind; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_sim_data {int num_chal; int /*<<< orphan*/  nonce_mt; int /*<<< orphan*/  k_aut; scalar_t__ rand; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_SIM_AT_MAC ; 
 int /*<<< orphan*/  EAP_SIM_AT_RAND ; 
 int /*<<< orphan*/  EAP_SIM_AT_RESULT_IND ; 
 int /*<<< orphan*/  EAP_SIM_NONCE_MT_LEN ; 
 int /*<<< orphan*/  EAP_SIM_SUBTYPE_CHALLENGE ; 
 int /*<<< orphan*/  EAP_TYPE_SIM ; 
 int GSM_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_sim_build_encr (struct eap_sm*,struct eap_sim_data*,struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eap_sim_msg_add_mac (struct eap_sim_msg*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_free (struct eap_sim_msg*) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_sim_build_challenge(struct eap_sm *sm,
					       struct eap_sim_data *data,
					       u8 id)
{
	struct eap_sim_msg *msg;

	wpa_printf(MSG_DEBUG, "EAP-SIM: Generating Challenge");
	msg = eap_sim_msg_init(EAP_CODE_REQUEST, id, EAP_TYPE_SIM,
			       EAP_SIM_SUBTYPE_CHALLENGE);
	wpa_printf(MSG_DEBUG, "   AT_RAND");
	eap_sim_msg_add(msg, EAP_SIM_AT_RAND, 0, (u8 *) data->rand,
			data->num_chal * GSM_RAND_LEN);

	if (eap_sim_build_encr(sm, data, msg, 0, NULL)) {
		eap_sim_msg_free(msg);
		return NULL;
	}

	if (sm->eap_sim_aka_result_ind) {
		wpa_printf(MSG_DEBUG, "   AT_RESULT_IND");
		eap_sim_msg_add(msg, EAP_SIM_AT_RESULT_IND, 0, NULL, 0);
	}

	wpa_printf(MSG_DEBUG, "   AT_MAC");
	eap_sim_msg_add_mac(msg, EAP_SIM_AT_MAC);
	return eap_sim_msg_finish(msg, EAP_TYPE_SIM, data->k_aut,
				  data->nonce_mt, EAP_SIM_NONCE_MT_LEN);
}