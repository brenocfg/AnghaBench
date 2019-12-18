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
struct eap_aka_data {int /*<<< orphan*/  k_aut; int /*<<< orphan*/  eap_method; int /*<<< orphan*/  k_encr; int /*<<< orphan*/  counter; scalar_t__ reauth; scalar_t__ use_result_ind; int /*<<< orphan*/  notification; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_NOTIFICATION ; 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_SIM_AT_COUNTER ; 
 int /*<<< orphan*/  EAP_SIM_AT_ENCR_DATA ; 
 int /*<<< orphan*/  EAP_SIM_AT_IV ; 
 int /*<<< orphan*/  EAP_SIM_AT_MAC ; 
 int /*<<< orphan*/  EAP_SIM_AT_NOTIFICATION ; 
 int /*<<< orphan*/  EAP_SIM_AT_PADDING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sim_msg_add_encr_end (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_encr_start (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_mac (struct eap_sim_msg*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_free (struct eap_sim_msg*) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_aka_build_notification(struct eap_sm *sm,
						  struct eap_aka_data *data,
						  u8 id)
{
	struct eap_sim_msg *msg;

	wpa_printf(MSG_DEBUG, "EAP-AKA: Generating Notification");
	msg = eap_sim_msg_init(EAP_CODE_REQUEST, id, data->eap_method,
			       EAP_AKA_SUBTYPE_NOTIFICATION);
	wpa_printf(MSG_DEBUG, "   AT_NOTIFICATION (%d)", data->notification);
	eap_sim_msg_add(msg, EAP_SIM_AT_NOTIFICATION, data->notification,
			NULL, 0);
	if (data->use_result_ind) {
		if (data->reauth) {
			wpa_printf(MSG_DEBUG, "   AT_IV");
			wpa_printf(MSG_DEBUG, "   AT_ENCR_DATA");
			eap_sim_msg_add_encr_start(msg, EAP_SIM_AT_IV,
						   EAP_SIM_AT_ENCR_DATA);
			wpa_printf(MSG_DEBUG, "   *AT_COUNTER (%u)",
				   data->counter);
			eap_sim_msg_add(msg, EAP_SIM_AT_COUNTER, data->counter,
					NULL, 0);

			if (eap_sim_msg_add_encr_end(msg, data->k_encr,
						     EAP_SIM_AT_PADDING)) {
				wpa_printf(MSG_WARNING, "EAP-AKA: Failed to "
					   "encrypt AT_ENCR_DATA");
				eap_sim_msg_free(msg);
				return NULL;
			}
		}

		wpa_printf(MSG_DEBUG, "   AT_MAC");
		eap_sim_msg_add_mac(msg, EAP_SIM_AT_MAC);
	}
	return eap_sim_msg_finish(msg, data->eap_method, data->k_aut, NULL, 0);
}