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
struct eap_psk_data {int state; } ;
struct eap_method_ret {scalar_t__ methodState; void* allowNotifications; void* ignore; int /*<<< orphan*/  decision; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  EAP_TYPE_PSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FALSE ; 
 scalar_t__ METHOD_DONE ; 
 scalar_t__ METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  PSK_DONE 130 
#define  PSK_INIT 129 
#define  PSK_MAC_SENT 128 
 void* TRUE ; 
 int /*<<< orphan*/ * eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 struct wpabuf* eap_psk_process_1 (struct eap_psk_data*,struct eap_method_ret*,struct wpabuf const*) ; 
 struct wpabuf* eap_psk_process_3 (struct eap_psk_data*,struct eap_method_ret*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_psk_process(struct eap_sm *sm, void *priv,
				       struct eap_method_ret *ret,
				       const struct wpabuf *reqData)
{
	struct eap_psk_data *data = priv;
	const u8 *pos;
	struct wpabuf *resp = NULL;
	size_t len;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_PSK, reqData, &len);
	if (pos == NULL) {
		ret->ignore = TRUE;
		return NULL;
	}

	ret->ignore = FALSE;
	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_FAIL;
	ret->allowNotifications = TRUE;

	switch (data->state) {
	case PSK_INIT:
		resp = eap_psk_process_1(data, ret, reqData);
		break;
	case PSK_MAC_SENT:
		resp = eap_psk_process_3(data, ret, reqData);
		break;
	case PSK_DONE:
		wpa_printf(MSG_DEBUG, "EAP-PSK: in DONE state - ignore "
			   "unexpected message");
		ret->ignore = TRUE;
		return NULL;
	}

	if (ret->methodState == METHOD_DONE) {
		ret->allowNotifications = FALSE;
	}

	return resp;
}