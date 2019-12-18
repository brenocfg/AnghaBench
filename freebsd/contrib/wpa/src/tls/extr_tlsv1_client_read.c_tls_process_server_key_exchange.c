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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cipher_suite; } ;
struct tlsv1_client {int flags; int /*<<< orphan*/  state; TYPE_1__ rl; } ;
struct tls_cipher_suite {scalar_t__ key_exchange; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SERVER_CERTIFICATE_REQUEST ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_ALERT_UNEXPECTED_MESSAGE ; 
 int TLS_CONN_REQUEST_OCSP ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CERTIFICATE_REQUEST ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CERTIFICATE_STATUS ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_SERVER_HELLO_DONE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_SERVER_KEY_EXCHANGE ; 
 scalar_t__ TLS_KEY_X_DHE_RSA ; 
 scalar_t__ TLS_KEY_X_DH_anon ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tls_cipher_suite* tls_get_cipher_suite (int /*<<< orphan*/ ) ; 
 int tls_process_certificate_request (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int tls_process_certificate_status (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int tls_process_server_hello_done (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_server_key_exchange_allowed (int /*<<< orphan*/ ) ; 
 scalar_t__ tlsv1_process_diffie_hellman (struct tlsv1_client*,scalar_t__ const*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_process_server_key_exchange(struct tlsv1_client *conn, u8 ct,
					   const u8 *in_data, size_t *in_len)
{
	const u8 *pos, *end;
	size_t left, len;
	u8 type;
	const struct tls_cipher_suite *suite;

	if (ct != TLS_CONTENT_TYPE_HANDSHAKE) {
		wpa_printf(MSG_DEBUG, "TLSv1: Expected Handshake; "
			   "received content type 0x%x", ct);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	pos = in_data;
	left = *in_len;

	if (left < 4) {
		wpa_printf(MSG_DEBUG, "TLSv1: Too short ServerKeyExchange "
			   "(Left=%lu)", (unsigned long) left);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	type = *pos++;
	len = WPA_GET_BE24(pos);
	pos += 3;
	left -= 4;

	if (len > left) {
		wpa_printf(MSG_DEBUG, "TLSv1: Mismatch in ServerKeyExchange "
			   "length (len=%lu != left=%lu)",
			   (unsigned long) len, (unsigned long) left);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	end = pos + len;

	if ((conn->flags & TLS_CONN_REQUEST_OCSP) &&
	    type == TLS_HANDSHAKE_TYPE_CERTIFICATE_STATUS)
		return tls_process_certificate_status(conn, ct, in_data,
						      in_len);
	if (type == TLS_HANDSHAKE_TYPE_CERTIFICATE_REQUEST)
		return tls_process_certificate_request(conn, ct, in_data,
						       in_len);
	if (type == TLS_HANDSHAKE_TYPE_SERVER_HELLO_DONE)
		return tls_process_server_hello_done(conn, ct, in_data,
						     in_len);
	if (type != TLS_HANDSHAKE_TYPE_SERVER_KEY_EXCHANGE) {
		wpa_printf(MSG_DEBUG, "TLSv1: Received unexpected handshake "
			   "message %d (expected ServerKeyExchange/"
			   "CertificateRequest/ServerHelloDone%s)", type,
			   (conn->flags & TLS_CONN_REQUEST_OCSP) ?
			   "/CertificateStatus" : "");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "TLSv1: Received ServerKeyExchange");

	if (!tls_server_key_exchange_allowed(conn->rl.cipher_suite)) {
		wpa_printf(MSG_DEBUG, "TLSv1: ServerKeyExchange not allowed "
			   "with the selected cipher suite");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	wpa_hexdump(MSG_DEBUG, "TLSv1: ServerKeyExchange", pos, len);
	suite = tls_get_cipher_suite(conn->rl.cipher_suite);
	if (suite && (suite->key_exchange == TLS_KEY_X_DH_anon ||
		      suite->key_exchange == TLS_KEY_X_DHE_RSA)) {
		if (tlsv1_process_diffie_hellman(conn, pos, len,
						 suite->key_exchange) < 0) {
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
				  TLS_ALERT_DECODE_ERROR);
			return -1;
		}
	} else {
		wpa_printf(MSG_DEBUG, "TLSv1: UnexpectedServerKeyExchange");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	*in_len = end - in_data;

	conn->state = SERVER_CERTIFICATE_REQUEST;

	return 0;
}