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
struct eap_sm {int server_id_len; int /*<<< orphan*/  server_id; } ;
struct eap_mschapv2_hdr {int /*<<< orphan*/  ms_length; int /*<<< orphan*/  mschapv2_id; int /*<<< orphan*/  op_code; } ;
struct eap_mschapv2_data {int /*<<< orphan*/  auth_challenge; int /*<<< orphan*/  auth_challenge_from_tls; void* state; } ;

/* Variables and functions */
 int CHALLENGE_LEN ; 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_TYPE_MSCHAPV2 ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FAILURE ; 
 int /*<<< orphan*/  MSCHAPV2_OP_CHALLENGE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,size_t) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct eap_mschapv2_hdr* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_mschapv2_build_challenge(
	struct eap_sm *sm, struct eap_mschapv2_data *data, u8 id)
{
	struct wpabuf *req;
	struct eap_mschapv2_hdr *ms;
	size_t ms_len;

	if (!data->auth_challenge_from_tls &&
	    random_get_bytes(data->auth_challenge, CHALLENGE_LEN)) {
		wpa_printf(MSG_ERROR, "EAP-MSCHAPV2: Failed to get random "
			   "data");
		data->state = FAILURE;
		return NULL;
	}

	ms_len = sizeof(*ms) + 1 + CHALLENGE_LEN + sm->server_id_len;
	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_MSCHAPV2, ms_len,
			    EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-MSCHAPV2: Failed to allocate memory"
			   " for request");
		data->state = FAILURE;
		return NULL;
	}

	ms = wpabuf_put(req, sizeof(*ms));
	ms->op_code = MSCHAPV2_OP_CHALLENGE;
	ms->mschapv2_id = id;
	WPA_PUT_BE16(ms->ms_length, ms_len);

	wpabuf_put_u8(req, CHALLENGE_LEN);
	if (!data->auth_challenge_from_tls)
		wpabuf_put_data(req, data->auth_challenge, CHALLENGE_LEN);
	else
		wpabuf_put(req, CHALLENGE_LEN);
	wpa_hexdump(MSG_MSGDUMP, "EAP-MSCHAPV2: Challenge",
		    data->auth_challenge, CHALLENGE_LEN);
	wpabuf_put_data(req, sm->server_id, sm->server_id_len);

	return req;
}