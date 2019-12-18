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
typedef  int u16 ;
struct wpabuf {int dummy; } ;
struct eap_sim_msg {int dummy; } ;
struct eap_aka_data {int /*<<< orphan*/  eap_method; int /*<<< orphan*/  k_encr; int /*<<< orphan*/  counter; scalar_t__ reauth; int /*<<< orphan*/ * k_aut; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_SUBTYPE_NOTIFICATION ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SIM_AT_COUNTER ; 
 int /*<<< orphan*/  EAP_SIM_AT_ENCR_DATA ; 
 int /*<<< orphan*/  EAP_SIM_AT_IV ; 
 int /*<<< orphan*/  EAP_SIM_AT_MAC ; 
 int /*<<< orphan*/  EAP_SIM_AT_PADDING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sim_msg_add_encr_end (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_encr_start (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_add_mac (struct eap_sim_msg*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_msg_free (struct eap_sim_msg*) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_aka_response_notification(struct eap_aka_data *data,
						     u8 id, u16 notification)
{
	struct eap_sim_msg *msg;
	u8 *k_aut = (notification & 0x4000) == 0 ? data->k_aut : NULL;

	wpa_printf(MSG_DEBUG, "Generating EAP-AKA Notification (id=%d)", id);
	msg = eap_sim_msg_init(EAP_CODE_RESPONSE, id, data->eap_method,
			       EAP_AKA_SUBTYPE_NOTIFICATION);
	if (k_aut && data->reauth) {
		wpa_printf(MSG_DEBUG, "   AT_IV");
		wpa_printf(MSG_DEBUG, "   AT_ENCR_DATA");
		eap_sim_msg_add_encr_start(msg, EAP_SIM_AT_IV,
					   EAP_SIM_AT_ENCR_DATA);
		wpa_printf(MSG_DEBUG, "   *AT_COUNTER %d", data->counter);
		eap_sim_msg_add(msg, EAP_SIM_AT_COUNTER, data->counter,
				NULL, 0);
		if (eap_sim_msg_add_encr_end(msg, data->k_encr,
					     EAP_SIM_AT_PADDING)) {
			wpa_printf(MSG_WARNING, "EAP-AKA: Failed to encrypt "
				   "AT_ENCR_DATA");
			eap_sim_msg_free(msg);
			return NULL;
		}
	}
	if (k_aut) {
		wpa_printf(MSG_DEBUG, "   AT_MAC");
		eap_sim_msg_add_mac(msg, EAP_SIM_AT_MAC);
	}
	return eap_sim_msg_finish(msg, data->eap_method, k_aut, (u8 *) "", 0);
}