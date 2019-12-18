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
struct eap_sm {int /*<<< orphan*/  msg_ctx; } ;
struct eap_sim_attrs {int notification; } ;
struct eap_aka_data {scalar_t__ num_notification; int error_code; scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_UNABLE_TO_PROCESS_PACKET ; 
 int EAP_SIM_SUCCESS ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ RESULT_SUCCESS ; 
 int /*<<< orphan*/  SUCCESS ; 
 struct wpabuf* eap_aka_client_error (struct eap_aka_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_aka_process_notification_auth (struct eap_aka_data*,struct wpabuf const*,struct eap_sim_attrs*) ; 
 struct wpabuf* eap_aka_response_notification (struct eap_aka_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_report_notification (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_aka_process_notification(
	struct eap_sm *sm, struct eap_aka_data *data, u8 id,
	const struct wpabuf *reqData, struct eap_sim_attrs *attr)
{
	wpa_printf(MSG_DEBUG, "EAP-AKA: subtype Notification");
	if (data->num_notification > 0) {
		wpa_printf(MSG_INFO, "EAP-AKA: too many notification "
			   "rounds (only one allowed)");
		return eap_aka_client_error(data, id,
					    EAP_AKA_UNABLE_TO_PROCESS_PACKET);
	}
	data->num_notification++;
	if (attr->notification == -1) {
		wpa_printf(MSG_INFO, "EAP-AKA: no AT_NOTIFICATION in "
			   "Notification message");
		return eap_aka_client_error(data, id,
					    EAP_AKA_UNABLE_TO_PROCESS_PACKET);
	}

	if ((attr->notification & 0x4000) == 0 &&
	    eap_aka_process_notification_auth(data, reqData, attr)) {
		return eap_aka_client_error(data, id,
					    EAP_AKA_UNABLE_TO_PROCESS_PACKET);
	}

	eap_sim_report_notification(sm->msg_ctx, attr->notification, 1);
	if (attr->notification >= 0 && attr->notification < 32768) {
		data->error_code = attr->notification;
		eap_aka_state(data, FAILURE);
	} else if (attr->notification == EAP_SIM_SUCCESS &&
		   data->state == RESULT_SUCCESS)
		eap_aka_state(data, SUCCESS);
	return eap_aka_response_notification(data, id, attr->notification);
}