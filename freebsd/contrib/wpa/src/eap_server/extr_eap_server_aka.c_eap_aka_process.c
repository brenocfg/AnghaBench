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
struct eap_sim_attrs {int dummy; } ;
struct eap_aka_data {scalar_t__ eap_method; int state; void* notification; } ;

/* Variables and functions */
#define  CHALLENGE 131 
 scalar_t__ EAP_AKA_SUBTYPE_AUTHENTICATION_REJECT ; 
 scalar_t__ EAP_AKA_SUBTYPE_CLIENT_ERROR ; 
 scalar_t__ EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE ; 
 void* EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
#define  IDENTITY 130 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  NOTIFICATION 129 
#define  REAUTH 128 
 int /*<<< orphan*/  eap_aka_process_authentication_reject (struct eap_sm*,struct eap_aka_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_aka_process_challenge (struct eap_sm*,struct eap_aka_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_aka_process_client_error (struct eap_sm*,struct eap_aka_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_aka_process_identity (struct eap_sm*,struct eap_aka_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_aka_process_notification (struct eap_sm*,struct eap_aka_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_aka_process_reauth (struct eap_sm*,struct eap_aka_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_aka_process_sync_failure (struct eap_sm*,struct eap_aka_data*,struct wpabuf*,struct eap_sim_attrs*) ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int) ; 
 scalar_t__ eap_aka_subtype_ok (struct eap_aka_data*,scalar_t__) ; 
 scalar_t__* eap_hdr_validate (int /*<<< orphan*/ ,scalar_t__,struct wpabuf*,size_t*) ; 
 scalar_t__ eap_sim_parse_attr (scalar_t__ const*,scalar_t__ const*,struct eap_sim_attrs*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_aka_process(struct eap_sm *sm, void *priv,
			    struct wpabuf *respData)
{
	struct eap_aka_data *data = priv;
	const u8 *pos, *end;
	u8 subtype;
	size_t len;
	struct eap_sim_attrs attr;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, data->eap_method, respData,
			       &len);
	if (pos == NULL || len < 3)
		return;

	end = pos + len;
	subtype = *pos;
	pos += 3;

	if (eap_aka_subtype_ok(data, subtype)) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Unrecognized or unexpected "
			   "EAP-AKA Subtype in EAP Response");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	if (eap_sim_parse_attr(pos, end, &attr,
			       data->eap_method == EAP_TYPE_AKA_PRIME ? 2 : 1,
			       0)) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Failed to parse attributes");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	if (subtype == EAP_AKA_SUBTYPE_CLIENT_ERROR) {
		eap_aka_process_client_error(sm, data, respData, &attr);
		return;
	}

	if (subtype == EAP_AKA_SUBTYPE_AUTHENTICATION_REJECT) {
		eap_aka_process_authentication_reject(sm, data, respData,
						      &attr);
		return;
	}

	switch (data->state) {
	case IDENTITY:
		eap_aka_process_identity(sm, data, respData, &attr);
		break;
	case CHALLENGE:
		if (subtype == EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE) {
			eap_aka_process_sync_failure(sm, data, respData,
						     &attr);
		} else {
			eap_aka_process_challenge(sm, data, respData, &attr);
		}
		break;
	case REAUTH:
		eap_aka_process_reauth(sm, data, respData, &attr);
		break;
	case NOTIFICATION:
		eap_aka_process_notification(sm, data, respData, &attr);
		break;
	default:
		wpa_printf(MSG_DEBUG, "EAP-AKA: Unknown state %d in "
			   "process", data->state);
		break;
	}
}