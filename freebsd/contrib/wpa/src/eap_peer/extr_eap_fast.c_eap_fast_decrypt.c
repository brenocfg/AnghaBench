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
typedef  struct wpabuf const wpabuf ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {int dummy; } ;
struct eap_fast_data {int /*<<< orphan*/  ssl; int /*<<< orphan*/  fast_version; struct wpabuf const* pending_phase2_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_FAST ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int eap_fast_process_decrypted (struct eap_sm*,struct eap_fast_data*,struct eap_method_ret*,int /*<<< orphan*/ ,struct wpabuf const*,struct wpabuf const**) ; 
 int eap_peer_tls_decrypt (struct eap_sm*,int /*<<< orphan*/ *,struct wpabuf const*,struct wpabuf const**) ; 
 int eap_peer_tls_encrypt (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wpabuf const**) ; 
 int /*<<< orphan*/  eap_peer_tls_reset_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf const*) ; 
 int wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static int eap_fast_decrypt(struct eap_sm *sm, struct eap_fast_data *data,
			    struct eap_method_ret *ret, u8 identifier,
			    const struct wpabuf *in_data,
			    struct wpabuf **out_data)
{
	struct wpabuf *in_decrypted;
	int res;

	wpa_printf(MSG_DEBUG, "EAP-FAST: Received %lu bytes encrypted data for"
		   " Phase 2", (unsigned long) wpabuf_len(in_data));

	if (data->pending_phase2_req) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Pending Phase 2 request - "
			   "skip decryption and use old data");
		/* Clear TLS reassembly state. */
		eap_peer_tls_reset_input(&data->ssl);

		in_decrypted = data->pending_phase2_req;
		data->pending_phase2_req = NULL;
		goto continue_req;
	}

	if (wpabuf_len(in_data) == 0) {
		/* Received TLS ACK - requesting more fragments */
		return eap_peer_tls_encrypt(sm, &data->ssl, EAP_TYPE_FAST,
					    data->fast_version,
					    identifier, NULL, out_data);
	}

	res = eap_peer_tls_decrypt(sm, &data->ssl, in_data, &in_decrypted);
	if (res)
		return res;

continue_req:
	wpa_hexdump_buf(MSG_MSGDUMP, "EAP-FAST: Decrypted Phase 2 TLV(s)",
			in_decrypted);

	if (wpabuf_len(in_decrypted) < 4) {
		wpa_printf(MSG_INFO, "EAP-FAST: Too short Phase 2 "
			   "TLV frame (len=%lu)",
			   (unsigned long) wpabuf_len(in_decrypted));
		wpabuf_clear_free(in_decrypted);
		return -1;
	}

	res = eap_fast_process_decrypted(sm, data, ret, identifier,
					 in_decrypted, out_data);

	wpabuf_clear_free(in_decrypted);

	return res;
}