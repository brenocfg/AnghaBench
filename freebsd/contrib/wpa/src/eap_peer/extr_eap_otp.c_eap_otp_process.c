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
struct eap_method_ret {void* allowNotifications; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; void* ignore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_COND_SUCC ; 
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_TYPE_OTP ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FALSE ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 void* TRUE ; 
 int /*<<< orphan*/  eap_clear_config_otp (struct eap_sm*) ; 
 int /*<<< orphan*/ * eap_get_config_otp (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/ * eap_get_config_password (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/  eap_get_id (struct wpabuf const*) ; 
 int /*<<< orphan*/ * eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sm_request_otp (struct eap_sm*,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_otp_process(struct eap_sm *sm, void *priv,
				       struct eap_method_ret *ret,
				       const struct wpabuf *reqData)
{
	struct wpabuf *resp;
	const u8 *pos, *password;
	size_t password_len, len;
	int otp;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_OTP, reqData, &len);
	if (pos == NULL) {
		ret->ignore = TRUE;
		return NULL;
	}
	wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-OTP: Request message",
			  pos, len);

	password = eap_get_config_otp(sm, &password_len);
	if (password)
		otp = 1;
	else {
		password = eap_get_config_password(sm, &password_len);
		otp = 0;
	}

	if (password == NULL) {
		wpa_printf(MSG_INFO, "EAP-OTP: Password not configured");
		eap_sm_request_otp(sm, (const char *) pos, len);
		ret->ignore = TRUE;
		return NULL;
	}

	ret->ignore = FALSE;

	ret->methodState = METHOD_DONE;
	ret->decision = DECISION_COND_SUCC;
	ret->allowNotifications = FALSE;

	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_OTP, password_len,
			     EAP_CODE_RESPONSE, eap_get_id(reqData));
	if (resp == NULL)
		return NULL;
	wpabuf_put_data(resp, password, password_len);
	wpa_hexdump_ascii_key(MSG_MSGDUMP, "EAP-OTP: Response",
			      password, password_len);

	if (otp) {
		wpa_printf(MSG_DEBUG, "EAP-OTP: Forgetting used password");
		eap_clear_config_otp(sm);
	}

	return resp;
}