#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpabuf {int dummy; } ;
struct eap_sm {TYPE_1__* user; } ;
struct eap_mschapv2_data {int state; } ;
struct TYPE_2__ {int /*<<< orphan*/ * password; } ;

/* Variables and functions */
#define  CHALLENGE 130 
 int FAILURE ; 
#define  FAILURE_REQ 129 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  SUCCESS_REQ 128 
 int /*<<< orphan*/  eap_mschapv2_process_failure_resp (struct eap_sm*,struct eap_mschapv2_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  eap_mschapv2_process_response (struct eap_sm*,struct eap_mschapv2_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  eap_mschapv2_process_success_resp (struct eap_sm*,struct eap_mschapv2_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_mschapv2_process(struct eap_sm *sm, void *priv,
				 struct wpabuf *respData)
{
	struct eap_mschapv2_data *data = priv;

	if (sm->user == NULL || sm->user->password == NULL) {
		wpa_printf(MSG_INFO, "EAP-MSCHAPV2: Password not configured");
		data->state = FAILURE;
		return;
	}

	switch (data->state) {
	case CHALLENGE:
		eap_mschapv2_process_response(sm, data, respData);
		break;
	case SUCCESS_REQ:
		eap_mschapv2_process_success_resp(sm, data, respData);
		break;
	case FAILURE_REQ:
		eap_mschapv2_process_failure_resp(sm, data, respData);
		break;
	default:
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Unknown state %d in "
			   "process", data->state);
		break;
	}
}