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
typedef  scalar_t__ tls_key_exchange ;
struct TYPE_2__ {int /*<<< orphan*/  cipher_suite; } ;
struct tlsv1_server {int /*<<< orphan*/  state; TYPE_1__ rl; } ;
struct tls_cipher_suite {scalar_t__ key_exchange; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERTIFICATE_VERIFY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_ALERT_UNEXPECTED_MESSAGE ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CLIENT_KEY_EXCHANGE ; 
 scalar_t__ TLS_KEY_X_DHE_RSA ; 
 scalar_t__ TLS_KEY_X_DH_anon ; 
 scalar_t__ TLS_KEY_X_NULL ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
 struct tls_cipher_suite* tls_get_cipher_suite (int /*<<< orphan*/ ) ; 
 scalar_t__ tls_process_client_key_exchange_dh (struct tlsv1_server*,scalar_t__ const*,scalar_t__ const*) ; 
 scalar_t__ tls_process_client_key_exchange_rsa (struct tlsv1_server*,scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*,...) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,size_t) ; 

__attribute__((used)) static int tls_process_client_key_exchange(struct tlsv1_server *conn, u8 ct,
					   const u8 *in_data, size_t *in_len)
{
	const u8 *pos, *end;
	size_t left, len;
	u8 type;
	tls_key_exchange keyx;
	const struct tls_cipher_suite *suite;

	if (ct != TLS_CONTENT_TYPE_HANDSHAKE) {
		tlsv1_server_log(conn, "Expected Handshake; received content type 0x%x",
				 ct);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	pos = in_data;
	left = *in_len;

	if (left < 4) {
		tlsv1_server_log(conn, "Too short ClientKeyExchange (Left=%lu)",
				 (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	type = *pos++;
	len = WPA_GET_BE24(pos);
	pos += 3;
	left -= 4;

	if (len > left) {
		tlsv1_server_log(conn, "Mismatch in ClientKeyExchange length (len=%lu != left=%lu)",
				 (unsigned long) len, (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	end = pos + len;

	if (type != TLS_HANDSHAKE_TYPE_CLIENT_KEY_EXCHANGE) {
		tlsv1_server_log(conn, "Received unexpected handshake message %d (expected ClientKeyExchange)",
				 type);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	tlsv1_server_log(conn, "Received ClientKeyExchange");

	wpa_hexdump(MSG_DEBUG, "TLSv1: ClientKeyExchange", pos, len);

	suite = tls_get_cipher_suite(conn->rl.cipher_suite);
	if (suite == NULL)
		keyx = TLS_KEY_X_NULL;
	else
		keyx = suite->key_exchange;

	if ((keyx == TLS_KEY_X_DH_anon || keyx == TLS_KEY_X_DHE_RSA) &&
	    tls_process_client_key_exchange_dh(conn, pos, end) < 0)
		return -1;

	if (keyx != TLS_KEY_X_DH_anon && keyx != TLS_KEY_X_DHE_RSA &&
	    tls_process_client_key_exchange_rsa(conn, pos, end) < 0)
		return -1;

	*in_len = end - in_data;

	conn->state = CERTIFICATE_VERIFY;

	return 0;
}