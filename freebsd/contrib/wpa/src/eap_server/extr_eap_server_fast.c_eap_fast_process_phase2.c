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
struct wpabuf {int dummy; } ;
struct eap_sm {scalar_t__ method_pending; int /*<<< orphan*/  ssl_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_fast_data {struct wpabuf* pending_phase2_resp; TYPE_1__ ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 scalar_t__ METHOD_PENDING_WAIT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  eap_fast_process_phase2_tlvs (struct eap_sm*,struct eap_fast_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  eap_fast_state (struct eap_fast_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* tls_connection_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static void eap_fast_process_phase2(struct eap_sm *sm,
				    struct eap_fast_data *data,
				    struct wpabuf *in_buf)
{
	struct wpabuf *in_decrypted;

	wpa_printf(MSG_DEBUG, "EAP-FAST: Received %lu bytes encrypted data for"
		   " Phase 2", (unsigned long) wpabuf_len(in_buf));

	if (data->pending_phase2_resp) {
		wpa_printf(MSG_DEBUG, "EAP-PEAP: Pending Phase 2 response - "
			   "skip decryption and use old data");
		eap_fast_process_phase2_tlvs(sm, data,
					     data->pending_phase2_resp);
		wpabuf_free(data->pending_phase2_resp);
		data->pending_phase2_resp = NULL;
		return;
	}

	in_decrypted = tls_connection_decrypt(sm->ssl_ctx, data->ssl.conn,
					      in_buf);
	if (in_decrypted == NULL) {
		wpa_printf(MSG_INFO, "EAP-FAST: Failed to decrypt Phase 2 "
			   "data");
		eap_fast_state(data, FAILURE);
		return;
	}

	wpa_hexdump_buf_key(MSG_DEBUG, "EAP-FAST: Decrypted Phase 2 TLVs",
			    in_decrypted);

	eap_fast_process_phase2_tlvs(sm, data, in_decrypted);

	if (sm->method_pending == METHOD_PENDING_WAIT) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Phase2 method is in "
			   "pending wait state - save decrypted response");
		wpabuf_free(data->pending_phase2_resp);
		data->pending_phase2_resp = in_decrypted;
		return;
	}

	wpabuf_free(in_decrypted);
}