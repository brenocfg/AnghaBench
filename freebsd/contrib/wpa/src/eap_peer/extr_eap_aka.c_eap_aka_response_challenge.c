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
struct eap_aka_data {int res_len; int /*<<< orphan*/  k_aut; int /*<<< orphan*/  eap_method; scalar_t__ use_result_ind; int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_CHALLENGE ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SIM_AT_MAC ; 
 int /*<<< orphan*/  EAP_SIM_AT_RES ; 
 int /*<<< orphan*/  EAP_SIM_AT_RESULT_IND ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_aka_add_checkcode (struct eap_aka_data*,struct eap_sim_msg*) ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eap_sim_msg_add_mac (struct eap_sim_msg*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_aka_response_challenge(struct eap_aka_data *data,
						  u8 id)
{
	struct eap_sim_msg *msg;

	wpa_printf(MSG_DEBUG, "Generating EAP-AKA Challenge (id=%d)", id);
	msg = eap_sim_msg_init(EAP_CODE_RESPONSE, id, data->eap_method,
			       EAP_AKA_SUBTYPE_CHALLENGE);
	wpa_printf(MSG_DEBUG, "   AT_RES");
	eap_sim_msg_add(msg, EAP_SIM_AT_RES, data->res_len * 8,
			data->res, data->res_len);
	eap_aka_add_checkcode(data, msg);
	if (data->use_result_ind) {
		wpa_printf(MSG_DEBUG, "   AT_RESULT_IND");
		eap_sim_msg_add(msg, EAP_SIM_AT_RESULT_IND, 0, NULL, 0);
	}
	wpa_printf(MSG_DEBUG, "   AT_MAC");
	eap_sim_msg_add_mac(msg, EAP_SIM_AT_MAC);
	return eap_sim_msg_finish(msg, data->eap_method, data->k_aut, (u8 *) "",
				  0);
}