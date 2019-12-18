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
typedef  char u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_mschapv2_hdr {int dummy; } ;
struct eap_mschapv2_data {int success; scalar_t__ prev_error; int /*<<< orphan*/  auth_response; int /*<<< orphan*/  auth_response_valid; } ;
struct eap_method_ret {int /*<<< orphan*/  allowNotifications; int /*<<< orphan*/  decision; void* methodState; int /*<<< orphan*/  ignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  DECISION_UNCOND_SUCC ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_TYPE_MSCHAPV2 ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 scalar_t__ ERROR_PASSWD_EXPIRED ; 
 int /*<<< orphan*/  FALSE ; 
 void* METHOD_DONE ; 
 int MSCHAPV2_AUTH_RESPONSE_LEN ; 
 int /*<<< orphan*/  MSCHAPV2_OP_SUCCESS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eap_mschapv2_password_changed (struct eap_sm*,struct eap_mschapv2_data*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char) ; 
 scalar_t__ mschapv2_verify_auth_response (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_mschapv2_success(struct eap_sm *sm,
					    struct eap_mschapv2_data *data,
					    struct eap_method_ret *ret,
					    const struct eap_mschapv2_hdr *req,
					    size_t req_len, u8 id)
{
	struct wpabuf *resp;
	const u8 *pos;
	size_t len;

	wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Received success");
	len = req_len - sizeof(*req);
	pos = (const u8 *) (req + 1);
	if (!data->auth_response_valid ||
	    mschapv2_verify_auth_response(data->auth_response, pos, len)) {
		wpa_printf(MSG_WARNING, "EAP-MSCHAPV2: Invalid authenticator "
			   "response in success request");
		ret->methodState = METHOD_DONE;
		ret->decision = DECISION_FAIL;
		return NULL;
	}
	pos += 2 + 2 * MSCHAPV2_AUTH_RESPONSE_LEN;
	len -= 2 + 2 * MSCHAPV2_AUTH_RESPONSE_LEN;
	while (len > 0 && *pos == ' ') {
		pos++;
		len--;
	}
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-MSCHAPV2: Success message",
			  pos, len);
	wpa_printf(MSG_INFO, "EAP-MSCHAPV2: Authentication succeeded");

	/* Note: Only op_code of the EAP-MSCHAPV2 header is included in success
	 * message. */
	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_MSCHAPV2, 1,
			     EAP_CODE_RESPONSE, id);
	if (resp == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Failed to allocate "
			   "buffer for success response");
		ret->ignore = TRUE;
		return NULL;
	}

	wpabuf_put_u8(resp, MSCHAPV2_OP_SUCCESS); /* op_code */

	ret->methodState = METHOD_DONE;
	ret->decision = DECISION_UNCOND_SUCC;
	ret->allowNotifications = FALSE;
	data->success = 1;

	if (data->prev_error == ERROR_PASSWD_EXPIRED)
		eap_mschapv2_password_changed(sm, data);

	return resp;
}