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
struct eap_sake_hdr {scalar_t__ subtype; scalar_t__ session_id; } ;
struct eap_sake_data {int session_id_set; scalar_t__ session_id; } ;
struct eap_method_ret {scalar_t__ methodState; void* allowNotifications; void* ignore; int /*<<< orphan*/  decision; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
#define  EAP_SAKE_SUBTYPE_CHALLENGE 130 
#define  EAP_SAKE_SUBTYPE_CONFIRM 129 
#define  EAP_SAKE_SUBTYPE_IDENTITY 128 
 int /*<<< orphan*/  EAP_TYPE_SAKE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FALSE ; 
 scalar_t__ METHOD_DONE ; 
 scalar_t__ METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 void* TRUE ; 
 scalar_t__ eap_get_id (struct wpabuf const*) ; 
 scalar_t__* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 struct wpabuf* eap_sake_process_challenge (struct eap_sm*,struct eap_sake_data*,struct eap_method_ret*,scalar_t__,scalar_t__ const*,int) ; 
 struct wpabuf* eap_sake_process_confirm (struct eap_sm*,struct eap_sake_data*,struct eap_method_ret*,scalar_t__,struct wpabuf const*,scalar_t__ const*,int) ; 
 struct wpabuf* eap_sake_process_identity (struct eap_sm*,struct eap_sake_data*,struct eap_method_ret*,scalar_t__,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

__attribute__((used)) static struct wpabuf * eap_sake_process(struct eap_sm *sm, void *priv,
					struct eap_method_ret *ret,
					const struct wpabuf *reqData)
{
	struct eap_sake_data *data = priv;
	const struct eap_sake_hdr *req;
	struct wpabuf *resp;
	const u8 *pos, *end;
	size_t len;
	u8 subtype, session_id, id;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_SAKE, reqData, &len);
	if (pos == NULL || len < sizeof(struct eap_sake_hdr)) {
		ret->ignore = TRUE;
		return NULL;
	}

	req = (const struct eap_sake_hdr *) pos;
	end = pos + len;
	id = eap_get_id(reqData);
	subtype = req->subtype;
	session_id = req->session_id;
	pos = (const u8 *) (req + 1);

	wpa_printf(MSG_DEBUG, "EAP-SAKE: Received frame: subtype %d "
		   "session_id %d", subtype, session_id);
	wpa_hexdump(MSG_DEBUG, "EAP-SAKE: Received attributes",
		    pos, end - pos);

	if (data->session_id_set && data->session_id != session_id) {
		wpa_printf(MSG_INFO, "EAP-SAKE: Session ID mismatch (%d,%d)",
			   session_id, data->session_id);
		ret->ignore = TRUE;
		return NULL;
	}
	data->session_id = session_id;
	data->session_id_set = 1;

	ret->ignore = FALSE;
	ret->methodState = METHOD_MAY_CONT;
	ret->decision = DECISION_FAIL;
	ret->allowNotifications = TRUE;

	switch (subtype) {
	case EAP_SAKE_SUBTYPE_IDENTITY:
		resp = eap_sake_process_identity(sm, data, ret, id,
						 pos, end - pos);
		break;
	case EAP_SAKE_SUBTYPE_CHALLENGE:
		resp = eap_sake_process_challenge(sm, data, ret, id,
						  pos, end - pos);
		break;
	case EAP_SAKE_SUBTYPE_CONFIRM:
		resp = eap_sake_process_confirm(sm, data, ret, id, reqData,
						pos, end - pos);
		break;
	default:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Ignoring message with "
			   "unknown subtype %d", subtype);
		ret->ignore = TRUE;
		return NULL;
	}

	if (ret->methodState == METHOD_DONE)
		ret->allowNotifications = FALSE;

	return resp;
}