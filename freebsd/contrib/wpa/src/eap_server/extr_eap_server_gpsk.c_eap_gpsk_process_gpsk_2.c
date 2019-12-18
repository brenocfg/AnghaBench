#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  struct eap_gpsk_csuite {struct eap_gpsk_csuite const* specifier; int /*<<< orphan*/  vendor; } const eap_gpsk_csuite ;
typedef  struct eap_gpsk_csuite const u8 ;
typedef  int u16 ;
struct eap_sm {int server_id_len; struct eap_gpsk_csuite const* server_id; TYPE_1__* user; } ;
struct eap_gpsk_data {scalar_t__ state; int id_peer_len; int csuite_count; size_t id_len; void* specifier; int /*<<< orphan*/  vendor; int /*<<< orphan*/  sk_len; int /*<<< orphan*/  sk; struct eap_gpsk_csuite const* session_id; int /*<<< orphan*/ * id_peer; struct eap_gpsk_csuite const* rand_server; struct eap_gpsk_csuite const* rand_peer; int /*<<< orphan*/  pk_len; int /*<<< orphan*/  pk; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; struct eap_gpsk_csuite const* csuite_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  password_len; int /*<<< orphan*/ * password; } ;

/* Variables and functions */
 int EAP_GPSK_MAX_MIC_LEN ; 
 int EAP_GPSK_RAND_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_GPSK ; 
 int /*<<< orphan*/  FAILURE ; 
 scalar_t__ GPSK_1 ; 
 int /*<<< orphan*/  GPSK_3 ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 void* WPA_GET_BE16 (struct eap_gpsk_csuite const*) ; 
 int /*<<< orphan*/  WPA_GET_BE32 (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_gpsk_compute_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct eap_gpsk_csuite const*,int,struct eap_gpsk_csuite const*) ; 
 scalar_t__ eap_gpsk_derive_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct eap_gpsk_csuite const*,struct eap_gpsk_csuite const*,int /*<<< orphan*/ *,int,struct eap_gpsk_csuite const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ eap_gpsk_derive_session_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct eap_gpsk_csuite const*,struct eap_gpsk_csuite const*,int /*<<< orphan*/ *,int,struct eap_gpsk_csuite const*,int,int /*<<< orphan*/ ,struct eap_gpsk_csuite const*,size_t*) ; 
 size_t eap_gpsk_mic_len (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  eap_gpsk_state (struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (struct eap_gpsk_csuite const*,struct eap_gpsk_csuite const*,int) ; 
 scalar_t__ os_memcmp_const (struct eap_gpsk_csuite const*,struct eap_gpsk_csuite const*,size_t) ; 
 int /*<<< orphan*/  os_memcpy (struct eap_gpsk_csuite const*,struct eap_gpsk_csuite const*,int) ; 
 int /*<<< orphan*/ * os_memdup (struct eap_gpsk_csuite const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,struct eap_gpsk_csuite const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_gpsk_process_gpsk_2(struct eap_sm *sm,
				    struct eap_gpsk_data *data,
				    const u8 *payload, size_t payloadlen)
{
	const u8 *pos, *end;
	u16 alen;
	const struct eap_gpsk_csuite *csuite;
	size_t i, miclen;
	u8 mic[EAP_GPSK_MAX_MIC_LEN];

	if (data->state != GPSK_1)
		return;

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Received Response/GPSK-2");

	pos = payload;
	end = payload + payloadlen;

	if (end - pos < 2) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "ID_Peer length");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	alen = WPA_GET_BE16(pos);
	pos += 2;
	if (end - pos < alen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "ID_Peer");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	os_free(data->id_peer);
	data->id_peer = os_memdup(pos, alen);
	if (data->id_peer == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Not enough memory to store "
			   "%d-octet ID_Peer", alen);
		return;
	}
	data->id_peer_len = alen;
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-GPSK: ID_Peer",
			  data->id_peer, data->id_peer_len);
	pos += alen;

	if (end - pos < 2) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "ID_Server length");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	alen = WPA_GET_BE16(pos);
	pos += 2;
	if (end - pos < alen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "ID_Server");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	if (alen != sm->server_id_len ||
	    os_memcmp(pos, sm->server_id, alen) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: ID_Server in GPSK-1 and "
			   "GPSK-2 did not match");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	pos += alen;

	if (end - pos < EAP_GPSK_RAND_LEN) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "RAND_Peer");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	os_memcpy(data->rand_peer, pos, EAP_GPSK_RAND_LEN);
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Peer",
		    data->rand_peer, EAP_GPSK_RAND_LEN);
	pos += EAP_GPSK_RAND_LEN;

	if (end - pos < EAP_GPSK_RAND_LEN) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "RAND_Server");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	if (os_memcmp(data->rand_server, pos, EAP_GPSK_RAND_LEN) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: RAND_Server in GPSK-1 and "
			   "GPSK-2 did not match");
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Server in GPSK-1",
			    data->rand_server, EAP_GPSK_RAND_LEN);
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Server in GPSK-2",
			    pos, EAP_GPSK_RAND_LEN);
		eap_gpsk_state(data, FAILURE);
		return;
	}
	pos += EAP_GPSK_RAND_LEN;

	if (end - pos < 2) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "CSuite_List length");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	alen = WPA_GET_BE16(pos);
	pos += 2;
	if (end - pos < alen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "CSuite_List");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	if (alen != data->csuite_count * sizeof(struct eap_gpsk_csuite) ||
	    os_memcmp(pos, data->csuite_list, alen) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: CSuite_List in GPSK-1 and "
			   "GPSK-2 did not match");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	pos += alen;

	if (end - pos < (int) sizeof(*csuite)) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "CSuite_Sel");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	csuite = (const struct eap_gpsk_csuite *) pos;
	for (i = 0; i < data->csuite_count; i++) {
		if (os_memcmp(csuite, &data->csuite_list[i], sizeof(*csuite))
		    == 0)
			break;
	}
	if (i == data->csuite_count) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Peer selected unsupported "
			   "ciphersuite %d:%d",
			   WPA_GET_BE32(csuite->vendor),
			   WPA_GET_BE16(csuite->specifier));
		eap_gpsk_state(data, FAILURE);
		return;
	}
	data->vendor = WPA_GET_BE32(csuite->vendor);
	data->specifier = WPA_GET_BE16(csuite->specifier);
	wpa_printf(MSG_DEBUG, "EAP-GPSK: CSuite_Sel %d:%d",
		   data->vendor, data->specifier);
	pos += sizeof(*csuite);

	if (end - pos < 2) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "PD_Payload_1 length");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	alen = WPA_GET_BE16(pos);
	pos += 2;
	if (end - pos < alen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "PD_Payload_1");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: PD_Payload_1", pos, alen);
	pos += alen;

	if (sm->user == NULL || sm->user->password == NULL) {
		wpa_printf(MSG_INFO, "EAP-GPSK: No PSK/password configured "
			   "for the user");
		eap_gpsk_state(data, FAILURE);
		return;
	}

	if (eap_gpsk_derive_keys(sm->user->password, sm->user->password_len,
				 data->vendor, data->specifier,
				 data->rand_peer, data->rand_server,
				 data->id_peer, data->id_peer_len,
				 sm->server_id, sm->server_id_len,
				 data->msk, data->emsk,
				 data->sk, &data->sk_len,
				 data->pk, &data->pk_len) < 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to derive keys");
		eap_gpsk_state(data, FAILURE);
		return;
	}

	if (eap_gpsk_derive_session_id(sm->user->password,
				       sm->user->password_len,
				       data->vendor, data->specifier,
				       data->rand_peer, data->rand_server,
				       data->id_peer, data->id_peer_len,
				       sm->server_id, sm->server_id_len,
				       EAP_TYPE_GPSK,
				       data->session_id, &data->id_len) < 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to derive Session-Id");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Derived Session-Id",
		    data->session_id, data->id_len);

	miclen = eap_gpsk_mic_len(data->vendor, data->specifier);
	if (end - pos < (int) miclen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Message too short for MIC "
			   "(left=%lu miclen=%lu)",
			   (unsigned long) (end - pos),
			   (unsigned long) miclen);
		eap_gpsk_state(data, FAILURE);
		return;
	}
	if (eap_gpsk_compute_mic(data->sk, data->sk_len, data->vendor,
				 data->specifier, payload, pos - payload, mic)
	    < 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to compute MIC");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	if (os_memcmp_const(mic, pos, miclen) != 0) {
		wpa_printf(MSG_INFO, "EAP-GPSK: Incorrect MIC in GPSK-2");
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Received MIC", pos, miclen);
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Computed MIC", mic, miclen);
		eap_gpsk_state(data, FAILURE);
		return;
	}
	pos += miclen;

	if (pos != end) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Ignored %lu bytes of extra "
			   "data in the end of GPSK-2",
			   (unsigned long) (end - pos));
	}

	eap_gpsk_state(data, GPSK_3);
}