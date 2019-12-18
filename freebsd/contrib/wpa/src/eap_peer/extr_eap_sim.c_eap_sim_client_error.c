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
struct eap_sim_data {scalar_t__ num_notification; scalar_t__ num_id_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_SIM_AT_CLIENT_ERROR_CODE ; 
 int /*<<< orphan*/  EAP_SIM_SUBTYPE_CLIENT_ERROR ; 
 int /*<<< orphan*/  EAP_TYPE_SIM ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sim_msg_finish (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct eap_sim_msg* eap_sim_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_state (struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct wpabuf * eap_sim_client_error(struct eap_sim_data *data, u8 id,
					    int err)
{
	struct eap_sim_msg *msg;

	eap_sim_state(data, FAILURE);
	data->num_id_req = 0;
	data->num_notification = 0;

	wpa_printf(MSG_DEBUG, "EAP-SIM: Send Client-Error (error code %d)",
		   err);
	msg = eap_sim_msg_init(EAP_CODE_RESPONSE, id, EAP_TYPE_SIM,
			       EAP_SIM_SUBTYPE_CLIENT_ERROR);
	eap_sim_msg_add(msg, EAP_SIM_AT_CLIENT_ERROR_CODE, err, NULL, 0);
	return eap_sim_msg_finish(msg, EAP_TYPE_SIM, NULL, NULL, 0);
}