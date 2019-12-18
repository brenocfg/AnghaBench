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
struct eap_md5_data {void* state; int /*<<< orphan*/  challenge; } ;

/* Variables and functions */
 scalar_t__ CHALLENGE_LEN ; 
 void* CONTINUE ; 
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_TYPE_MD5 ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FAILURE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

__attribute__((used)) static struct wpabuf * eap_md5_buildReq(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_md5_data *data = priv;
	struct wpabuf *req;

	if (random_get_bytes(data->challenge, CHALLENGE_LEN)) {
		wpa_printf(MSG_ERROR, "EAP-MD5: Failed to get random data");
		data->state = FAILURE;
		return NULL;
	}

	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_MD5, 1 + CHALLENGE_LEN,
			    EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-MD5: Failed to allocate memory for "
			   "request");
		data->state = FAILURE;
		return NULL;
	}

	wpabuf_put_u8(req, CHALLENGE_LEN);
	wpabuf_put_data(req, data->challenge, CHALLENGE_LEN);
	wpa_hexdump(MSG_MSGDUMP, "EAP-MD5: Challenge", data->challenge,
		    CHALLENGE_LEN);

	data->state = CONTINUE;

	return req;
}