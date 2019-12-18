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
struct eap_sim_data {int num_chal; scalar_t__ sres; int /*<<< orphan*/  k_aut; scalar_t__ use_result_ind; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SIM_AT_MAC ; 
 int /*<<< orphan*/  EAP_SIM_AT_RESULT_IND ; 
 int EAP_SIM_SRES_LEN ; 
 int /*<<< orphan*/  EAP_SIM_SUBTYPE_CHALLENGE ; 
 int /*<<< orphan*/  EAP_TYPE_SIM ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_mac (struct eap_sim_msg*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_sim_response_challenge(struct eap_sim_data *data,
						  u8 id)
{
	struct eap_sim_msg *msg;

	wpa_printf(MSG_DEBUG, "Generating EAP-SIM Challenge (id=%d)", id);
	msg = eap_sim_msg_init(EAP_CODE_RESPONSE, id, EAP_TYPE_SIM,
			       EAP_SIM_SUBTYPE_CHALLENGE);
	if (data->use_result_ind) {
		wpa_printf(MSG_DEBUG, "   AT_RESULT_IND");
		eap_sim_msg_add(msg, EAP_SIM_AT_RESULT_IND, 0, NULL, 0);
	}
	wpa_printf(MSG_DEBUG, "   AT_MAC");
	eap_sim_msg_add_mac(msg, EAP_SIM_AT_MAC);
	return eap_sim_msg_finish(msg, EAP_TYPE_SIM, data->k_aut,
				  (u8 *) data->sres,
				  data->num_chal * EAP_SIM_SRES_LEN);
}