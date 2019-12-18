#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpabuf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tls_out; int /*<<< orphan*/  conn; scalar_t__ tls_v13; struct wpabuf* tls_in; } ;
struct eap_tls_data {scalar_t__ state; TYPE_1__ ssl; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ SUCCESS ; 
 struct wpabuf* eap_server_tls_encrypt (struct eap_sm*,TYPE_1__*,struct wpabuf*) ; 
 scalar_t__ eap_server_tls_phase1 (struct eap_sm*,TYPE_1__*) ; 
 int /*<<< orphan*/  eap_tls_state (struct eap_tls_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (int /*<<< orphan*/ ,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void eap_tls_process_msg(struct eap_sm *sm, void *priv,
				const struct wpabuf *respData)
{
	struct eap_tls_data *data = priv;
	if (data->state == SUCCESS && wpabuf_len(data->ssl.tls_in) == 0) {
		wpa_printf(MSG_DEBUG, "EAP-TLS: Client acknowledged final TLS "
			   "handshake message");
		return;
	}
	if (eap_server_tls_phase1(sm, &data->ssl) < 0) {
		eap_tls_state(data, FAILURE);
		return;
	}

	if (data->ssl.tls_v13 &&
	    tls_connection_established(sm->ssl_ctx, data->ssl.conn)) {
		struct wpabuf *plain, *encr;

		wpa_printf(MSG_DEBUG,
			   "EAP-TLS: Send empty application data to indicate end of exchange");
		/* FIX: This should be an empty application data based on
		 * draft-ietf-emu-eap-tls13-05, but OpenSSL does not allow zero
		 * length payload (SSL_write() documentation explicitly
		 * describes this as not allowed), so work around that for now
		 * by sending out a payload of one octet. Hopefully the draft
		 * specification will change to allow this so that no crypto
		 * library changes are needed. */
		plain = wpabuf_alloc(1);
		if (!plain)
			return;
		wpabuf_put_u8(plain, 0);
		encr = eap_server_tls_encrypt(sm, &data->ssl, plain);
		wpabuf_free(plain);
		if (!encr)
			return;
		if (wpabuf_resize(&data->ssl.tls_out, wpabuf_len(encr)) < 0) {
			wpa_printf(MSG_INFO,
				   "EAP-TLS: Failed to resize output buffer");
			wpabuf_free(encr);
			return;
		}
		wpabuf_put_buf(data->ssl.tls_out, encr);
		wpa_hexdump_buf(MSG_DEBUG,
				"EAP-TLS: Data appended to the message", encr);
		wpabuf_free(encr);
	}
}