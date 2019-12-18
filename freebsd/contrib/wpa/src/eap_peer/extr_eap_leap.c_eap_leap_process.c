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
struct eap_sm {void* leap_done; } ;
struct eap_method_ret {void* ignore; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; void* allowNotifications; } ;
struct eap_hdr {int code; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
#define  EAP_CODE_REQUEST 130 
#define  EAP_CODE_RESPONSE 129 
#define  EAP_CODE_SUCCESS 128 
 void* FALSE ; 
 int /*<<< orphan*/  METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_INFO ; 
 void* TRUE ; 
 int be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * eap_get_config_password (struct eap_sm*,size_t*) ; 
 struct wpabuf* eap_leap_process_request (struct eap_sm*,void*,struct eap_method_ret*,struct wpabuf const*) ; 
 struct wpabuf* eap_leap_process_response (struct eap_sm*,void*,struct eap_method_ret*,struct wpabuf const*) ; 
 struct wpabuf* eap_leap_process_success (struct eap_sm*,void*,struct eap_method_ret*,struct wpabuf const*) ; 
 int /*<<< orphan*/  eap_sm_request_password (struct eap_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct eap_hdr* wpabuf_head (struct wpabuf const*) ; 
 int wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static struct wpabuf * eap_leap_process(struct eap_sm *sm, void *priv,
					struct eap_method_ret *ret,
					const struct wpabuf *reqData)
{
	const struct eap_hdr *eap;
	size_t password_len;
	const u8 *password;

	password = eap_get_config_password(sm, &password_len);
	if (password == NULL) {
		wpa_printf(MSG_INFO, "EAP-LEAP: Password not configured");
		eap_sm_request_password(sm);
		ret->ignore = TRUE;
		return NULL;
	}

	/*
	 * LEAP needs to be able to handle EAP-Success frame which does not
	 * include Type field. Consequently, eap_hdr_validate() cannot be used
	 * here. This validation will be done separately for EAP-Request and
	 * EAP-Response frames.
	 */
	eap = wpabuf_head(reqData);
	if (wpabuf_len(reqData) < sizeof(*eap) ||
	    be_to_host16(eap->length) > wpabuf_len(reqData)) {
		wpa_printf(MSG_INFO, "EAP-LEAP: Invalid frame");
		ret->ignore = TRUE;
		return NULL;
	}

	ret->ignore = FALSE;
	ret->allowNotifications = TRUE;
	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_FAIL;

	sm->leap_done = FALSE;

	switch (eap->code) {
	case EAP_CODE_REQUEST:
		return eap_leap_process_request(sm, priv, ret, reqData);
	case EAP_CODE_SUCCESS:
		return eap_leap_process_success(sm, priv, ret, reqData);
	case EAP_CODE_RESPONSE:
		return eap_leap_process_response(sm, priv, ret, reqData);
	default:
		wpa_printf(MSG_INFO, "EAP-LEAP: Unexpected EAP code (%d) - "
			   "ignored", eap->code);
		ret->ignore = TRUE;
		return NULL;
	}
}