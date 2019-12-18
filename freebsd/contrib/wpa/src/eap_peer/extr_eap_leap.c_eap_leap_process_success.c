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
struct eap_method_ret {void* ignore; } ;
struct eap_leap_data {scalar_t__ state; int /*<<< orphan*/  ap_challenge; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_TYPE_LEAP ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 scalar_t__ LEAP_CHALLENGE_LEN ; 
 scalar_t__ LEAP_VERSION ; 
 scalar_t__ LEAP_WAIT_RESPONSE ; 
 scalar_t__ LEAP_WAIT_SUCCESS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 void* TRUE ; 
 int /*<<< orphan*/ * eap_get_config_identity (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/  eap_get_id (struct wpabuf const*) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

__attribute__((used)) static struct wpabuf * eap_leap_process_success(struct eap_sm *sm, void *priv,
						struct eap_method_ret *ret,
						const struct wpabuf *reqData)
{
	struct eap_leap_data *data = priv;
	struct wpabuf *resp;
	u8 *pos;
	const u8 *identity;
	size_t identity_len;

	wpa_printf(MSG_DEBUG, "EAP-LEAP: Processing EAP-Success");

	identity = eap_get_config_identity(sm, &identity_len);
	if (identity == NULL)
		return NULL;

	if (data->state != LEAP_WAIT_SUCCESS) {
		wpa_printf(MSG_INFO, "EAP-LEAP: EAP-Success received in "
			   "unexpected state (%d) - ignored", data->state);
		ret->ignore = TRUE;
		return NULL;
	}

	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_LEAP,
			     3 + LEAP_CHALLENGE_LEN + identity_len,
			     EAP_CODE_REQUEST, eap_get_id(reqData));
	if (resp == NULL)
		return NULL;
	wpabuf_put_u8(resp, LEAP_VERSION);
	wpabuf_put_u8(resp, 0); /* unused */
	wpabuf_put_u8(resp, LEAP_CHALLENGE_LEN);
	pos = wpabuf_put(resp, LEAP_CHALLENGE_LEN);
	if (random_get_bytes(pos, LEAP_CHALLENGE_LEN)) {
		wpa_printf(MSG_WARNING, "EAP-LEAP: Failed to read random data "
			   "for challenge");
		wpabuf_free(resp);
		ret->ignore = TRUE;
		return NULL;
	}
	os_memcpy(data->ap_challenge, pos, LEAP_CHALLENGE_LEN);
	wpa_hexdump(MSG_MSGDUMP, "EAP-LEAP: Challenge to AP/AS", pos,
		    LEAP_CHALLENGE_LEN);
	wpabuf_put_data(resp, identity, identity_len);

	data->state = LEAP_WAIT_RESPONSE;

	return resp;
}