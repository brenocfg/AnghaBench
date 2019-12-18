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
struct eap_gpsk_data {int /*<<< orphan*/  specifier; int /*<<< orphan*/  vendor; int /*<<< orphan*/  sk_len; int /*<<< orphan*/  sk; int /*<<< orphan*/  rand_server; int /*<<< orphan*/  rand_peer; } ;
struct eap_gpsk_csuite {int /*<<< orphan*/  specifier; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_GPSK_OPCODE_GPSK_3 ; 
 int EAP_GPSK_RAND_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_GPSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_gpsk_compute_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 size_t eap_gpsk_mic_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_gpsk_state (struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 void* wpabuf_put (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_gpsk_build_gpsk_3(struct eap_sm *sm,
					     struct eap_gpsk_data *data, u8 id)
{
	u8 *pos, *start;
	size_t len, miclen;
	struct eap_gpsk_csuite *csuite;
	struct wpabuf *req;

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Request/GPSK-3");

	miclen = eap_gpsk_mic_len(data->vendor, data->specifier);
	len = 1 + 2 * EAP_GPSK_RAND_LEN + 2 + sm->server_id_len +
		sizeof(struct eap_gpsk_csuite) + 2 + miclen;
	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_GPSK, len,
			    EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-GPSK: Failed to allocate memory "
			   "for request/GPSK-3");
		eap_gpsk_state(data, FAILURE);
		return NULL;
	}

	wpabuf_put_u8(req, EAP_GPSK_OPCODE_GPSK_3);
	start = wpabuf_put(req, 0);

	wpabuf_put_data(req, data->rand_peer, EAP_GPSK_RAND_LEN);
	wpabuf_put_data(req, data->rand_server, EAP_GPSK_RAND_LEN);
	wpabuf_put_be16(req, sm->server_id_len);
	wpabuf_put_data(req, sm->server_id, sm->server_id_len);
	csuite = wpabuf_put(req, sizeof(*csuite));
	WPA_PUT_BE32(csuite->vendor, data->vendor);
	WPA_PUT_BE16(csuite->specifier, data->specifier);

	/* no PD_Payload_2 */
	wpabuf_put_be16(req, 0);

	pos = wpabuf_put(req, miclen);
	if (eap_gpsk_compute_mic(data->sk, data->sk_len, data->vendor,
				 data->specifier, start, pos - start, pos) < 0)
	{
		wpabuf_free(req);
		eap_gpsk_state(data, FAILURE);
		return NULL;
	}

	return req;
}