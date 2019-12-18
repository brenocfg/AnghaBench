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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {void* ignore; void* allowNotifications; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; } ;
struct eap_gpsk_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
#define  EAP_GPSK_OPCODE_GPSK_1 129 
#define  EAP_GPSK_OPCODE_GPSK_3 128 
 int /*<<< orphan*/  EAP_TYPE_GPSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FALSE ; 
 int /*<<< orphan*/  METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* TRUE ; 
 int eap_get_id (struct wpabuf const*) ; 
 struct wpabuf* eap_gpsk_process_gpsk_1 (struct eap_sm*,struct eap_gpsk_data*,struct eap_method_ret*,int,int const*,size_t) ; 
 struct wpabuf* eap_gpsk_process_gpsk_3 (struct eap_sm*,struct eap_gpsk_data*,struct eap_method_ret*,int,int const*,size_t) ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct wpabuf * eap_gpsk_process(struct eap_sm *sm, void *priv,
					struct eap_method_ret *ret,
					const struct wpabuf *reqData)
{
	struct eap_gpsk_data *data = priv;
	struct wpabuf *resp;
	const u8 *pos;
	size_t len;
	u8 opcode, id;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_GPSK, reqData, &len);
	if (pos == NULL || len < 1) {
		ret->ignore = TRUE;
		return NULL;
	}

	id = eap_get_id(reqData);
	opcode = *pos++;
	len--;
	wpa_printf(MSG_DEBUG, "EAP-GPSK: Received frame: opcode %d", opcode);

	ret->ignore = FALSE;
	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_FAIL;
	ret->allowNotifications = FALSE;

	switch (opcode) {
	case EAP_GPSK_OPCODE_GPSK_1:
		resp = eap_gpsk_process_gpsk_1(sm, data, ret, id, pos, len);
		break;
	case EAP_GPSK_OPCODE_GPSK_3:
		resp = eap_gpsk_process_gpsk_3(sm, data, ret, id, pos, len);
		break;
	default:
		wpa_printf(MSG_DEBUG,
			   "EAP-GPSK: Ignoring message with unknown opcode %d",
			   opcode);
		ret->ignore = TRUE;
		return NULL;
	}

	return resp;
}