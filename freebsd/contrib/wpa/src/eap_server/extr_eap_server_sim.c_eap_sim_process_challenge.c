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
struct eap_sm {int /*<<< orphan*/  eap_sim_db_priv; scalar_t__ eap_sim_aka_result_ind; } ;
struct eap_sim_data {int num_chal; int use_result_ind; int /*<<< orphan*/ * next_reauth_id; int /*<<< orphan*/  mk; scalar_t__ counter; int /*<<< orphan*/  permanent; int /*<<< orphan*/ * next_pseudonym; int /*<<< orphan*/  notification; scalar_t__ sres; int /*<<< orphan*/  k_aut; } ;
struct eap_sim_attrs {scalar_t__ result_ind; int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH ; 
 int EAP_SIM_SRES_LEN ; 
 int /*<<< orphan*/  EAP_SIM_SUCCESS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  NOTIFICATION ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  eap_sim_db_add_pseudonym (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_sim_db_add_reauth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_state (struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sim_verify_mac (int /*<<< orphan*/ ,struct wpabuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_sim_process_challenge(struct eap_sm *sm,
				      struct eap_sim_data *data,
				      struct wpabuf *respData,
				      struct eap_sim_attrs *attr)
{
	if (attr->mac == NULL ||
	    eap_sim_verify_mac(data->k_aut, respData, attr->mac,
			       (u8 *) data->sres,
			       data->num_chal * EAP_SIM_SRES_LEN)) {
		wpa_printf(MSG_WARNING, "EAP-SIM: Challenge message "
			   "did not include valid AT_MAC");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_sim_state(data, NOTIFICATION);
		return;
	}

	wpa_printf(MSG_DEBUG, "EAP-SIM: Challenge response includes the "
		   "correct AT_MAC");
	if (sm->eap_sim_aka_result_ind && attr->result_ind) {
		data->use_result_ind = 1;
		data->notification = EAP_SIM_SUCCESS;
		eap_sim_state(data, NOTIFICATION);
	} else
		eap_sim_state(data, SUCCESS);

	if (data->next_pseudonym) {
		eap_sim_db_add_pseudonym(sm->eap_sim_db_priv, data->permanent,
					 data->next_pseudonym);
		data->next_pseudonym = NULL;
	}
	if (data->next_reauth_id) {
		eap_sim_db_add_reauth(sm->eap_sim_db_priv, data->permanent,
				      data->next_reauth_id, data->counter + 1,
				      data->mk);
		data->next_reauth_id = NULL;
	}
}