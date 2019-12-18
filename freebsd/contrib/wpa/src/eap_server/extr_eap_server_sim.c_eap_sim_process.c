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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_sim_data {int state; void* notification; } ;
struct eap_sim_attrs {int dummy; } ;

/* Variables and functions */
#define  CHALLENGE 131 
 void* EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH ; 
 scalar_t__ EAP_SIM_SUBTYPE_CLIENT_ERROR ; 
 int /*<<< orphan*/  EAP_TYPE_SIM ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  NOTIFICATION 130 
#define  REAUTH 129 
#define  START 128 
 scalar_t__* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 scalar_t__ eap_sim_parse_attr (scalar_t__ const*,scalar_t__ const*,struct eap_sim_attrs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sim_process_challenge (struct eap_sm*,struct eap_sim_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_sim_process_client_error (struct eap_sm*,struct eap_sim_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_sim_process_notification (struct eap_sm*,struct eap_sim_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_sim_process_reauth (struct eap_sm*,struct eap_sim_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_sim_process_start (struct eap_sm*,struct eap_sim_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_sim_state (struct eap_sim_data*,int) ; 
 scalar_t__ eap_sim_unexpected_subtype (struct eap_sim_data*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_sim_process(struct eap_sm *sm, void *priv,
			    struct wpabuf *respData)
{
	struct eap_sim_data *data = priv;
	const u8 *pos, *end;
	u8 subtype;
	size_t len;
	struct eap_sim_attrs attr;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_SIM, respData, &len);
	if (pos == NULL || len < 3)
		return;

	end = pos + len;
	subtype = *pos;
	pos += 3;

	if (eap_sim_unexpected_subtype(data, subtype)) {
		wpa_printf(MSG_DEBUG, "EAP-SIM: Unrecognized or unexpected "
			   "EAP-SIM Subtype in EAP Response");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_sim_state(data, NOTIFICATION);
		return;
	}

	if (eap_sim_parse_attr(pos, end, &attr, 0, 0)) {
		wpa_printf(MSG_DEBUG, "EAP-SIM: Failed to parse attributes");
		if (subtype != EAP_SIM_SUBTYPE_CLIENT_ERROR &&
		    (data->state == START || data->state == CHALLENGE ||
		     data->state == REAUTH)) {
			data->notification =
				EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
			eap_sim_state(data, NOTIFICATION);
			return;
		}
		eap_sim_state(data, FAILURE);
		return;
	}

	if (subtype == EAP_SIM_SUBTYPE_CLIENT_ERROR) {
		eap_sim_process_client_error(sm, data, respData, &attr);
		return;
	}

	switch (data->state) {
	case START:
		eap_sim_process_start(sm, data, respData, &attr);
		break;
	case CHALLENGE:
		eap_sim_process_challenge(sm, data, respData, &attr);
		break;
	case REAUTH:
		eap_sim_process_reauth(sm, data, respData, &attr);
		break;
	case NOTIFICATION:
		eap_sim_process_notification(sm, data, respData, &attr);
		break;
	default:
		wpa_printf(MSG_DEBUG, "EAP-SIM: Unknown state %d in "
			   "process", data->state);
		break;
	}
}