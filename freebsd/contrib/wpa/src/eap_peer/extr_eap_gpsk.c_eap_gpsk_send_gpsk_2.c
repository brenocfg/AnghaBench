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
struct eap_gpsk_data {int id_peer_len; int id_server_len; int id_len; int /*<<< orphan*/  specifier; int /*<<< orphan*/  vendor; int /*<<< orphan*/  sk_len; int /*<<< orphan*/  sk; int /*<<< orphan*/  const* session_id; int /*<<< orphan*/  const* id_server; int /*<<< orphan*/  const* id_peer; int /*<<< orphan*/  const* rand_server; int /*<<< orphan*/  const* rand_peer; int /*<<< orphan*/  psk_len; int /*<<< orphan*/  psk; int /*<<< orphan*/  pk_len; int /*<<< orphan*/  pk; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; } ;
struct eap_gpsk_csuite {int /*<<< orphan*/  specifier; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_RESPONSE ; 
 int /*<<< orphan*/  EAP_GPSK_OPCODE_GPSK_2 ; 
 int EAP_GPSK_RAND_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_GPSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_gpsk_compute_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ eap_gpsk_derive_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ eap_gpsk_derive_session_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int*) ; 
 size_t eap_gpsk_mic_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_gpsk_state (struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 void* wpabuf_put (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_gpsk_send_gpsk_2(struct eap_gpsk_data *data,
					    u8 identifier,
					    const u8 *csuite_list,
					    size_t csuite_list_len)
{
	struct wpabuf *resp;
	size_t len, miclen;
	u8 *rpos, *start;
	struct eap_gpsk_csuite *csuite;

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Sending Response/GPSK-2");

	miclen = eap_gpsk_mic_len(data->vendor, data->specifier);
	len = 1 + 2 + data->id_peer_len + 2 + data->id_server_len +
		2 * EAP_GPSK_RAND_LEN + 2 + csuite_list_len +
		sizeof(struct eap_gpsk_csuite) + 2 + miclen;

	resp = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_GPSK, len,
			     EAP_CODE_RESPONSE, identifier);
	if (resp == NULL)
		return NULL;

	wpabuf_put_u8(resp, EAP_GPSK_OPCODE_GPSK_2);
	start = wpabuf_put(resp, 0);

	wpa_hexdump_ascii(MSG_DEBUG, "EAP-GPSK: ID_Peer",
			  data->id_peer, data->id_peer_len);
	wpabuf_put_be16(resp, data->id_peer_len);
	wpabuf_put_data(resp, data->id_peer, data->id_peer_len);

	wpabuf_put_be16(resp, data->id_server_len);
	wpabuf_put_data(resp, data->id_server, data->id_server_len);

	if (random_get_bytes(data->rand_peer, EAP_GPSK_RAND_LEN)) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to get random data "
			   "for RAND_Peer");
		eap_gpsk_state(data, FAILURE);
		wpabuf_free(resp);
		return NULL;
	}
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Peer",
		    data->rand_peer, EAP_GPSK_RAND_LEN);
	wpabuf_put_data(resp, data->rand_peer, EAP_GPSK_RAND_LEN);
	wpabuf_put_data(resp, data->rand_server, EAP_GPSK_RAND_LEN);

	wpabuf_put_be16(resp, csuite_list_len);
	wpabuf_put_data(resp, csuite_list, csuite_list_len);

	csuite = wpabuf_put(resp, sizeof(*csuite));
	WPA_PUT_BE32(csuite->vendor, data->vendor);
	WPA_PUT_BE16(csuite->specifier, data->specifier);

	if (eap_gpsk_derive_keys(data->psk, data->psk_len,
				 data->vendor, data->specifier,
				 data->rand_peer, data->rand_server,
				 data->id_peer, data->id_peer_len,
				 data->id_server, data->id_server_len,
				 data->msk, data->emsk,
				 data->sk, &data->sk_len,
				 data->pk, &data->pk_len) < 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to derive keys");
		eap_gpsk_state(data, FAILURE);
		wpabuf_free(resp);
		return NULL;
	}

	if (eap_gpsk_derive_session_id(data->psk, data->psk_len,
				       data->vendor, data->specifier,
				       data->rand_peer, data->rand_server,
				       data->id_peer, data->id_peer_len,
				       data->id_server, data->id_server_len,
				       EAP_TYPE_GPSK,
				       data->session_id, &data->id_len) < 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to derive Session-Id");
		eap_gpsk_state(data, FAILURE);
		wpabuf_free(resp);
		return NULL;
	}
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Derived Session-Id",
		    data->session_id, data->id_len);

	/* No PD_Payload_1 */
	wpabuf_put_be16(resp, 0);

	rpos = wpabuf_put(resp, miclen);
	if (eap_gpsk_compute_mic(data->sk, data->sk_len, data->vendor,
				 data->specifier, start, rpos - start, rpos) <
	    0) {
		eap_gpsk_state(data, FAILURE);
		wpabuf_free(resp);
		return NULL;
	}

	return resp;
}