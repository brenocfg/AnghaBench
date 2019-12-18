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
typedef  scalar_t__ u8 ;
struct tlsv1_server {int state; int /*<<< orphan*/  verify; } ;

/* Variables and functions */
#define  CERTIFICATE_VERIFY 133 
#define  CHANGE_CIPHER_SPEC 132 
#define  CLIENT_CERTIFICATE 131 
#define  CLIENT_FINISHED 130 
#define  CLIENT_HELLO 129 
#define  CLIENT_KEY_EXCHANGE 128 
 int FAILED ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 scalar_t__ TLS_CONTENT_TYPE_ALERT ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  tls_process_certificate (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_certificate_verify (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_change_cipher_spec (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_client_finished (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_client_hello (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_process_client_key_exchange (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tls_verify_hash_add (int /*<<< orphan*/ *,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*,...) ; 

int tlsv1_server_process_handshake(struct tlsv1_server *conn, u8 ct,
				   const u8 *buf, size_t *len)
{
	if (ct == TLS_CONTENT_TYPE_ALERT) {
		if (*len < 2) {
			tlsv1_server_log(conn, "Alert underflow");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_DECODE_ERROR);
			return -1;
		}
		tlsv1_server_log(conn, "Received alert %d:%d", buf[0], buf[1]);
		*len = 2;
		conn->state = FAILED;
		return -1;
	}

	switch (conn->state) {
	case CLIENT_HELLO:
		if (tls_process_client_hello(conn, ct, buf, len))
			return -1;
		break;
	case CLIENT_CERTIFICATE:
		if (tls_process_certificate(conn, ct, buf, len))
			return -1;
		break;
	case CLIENT_KEY_EXCHANGE:
		if (tls_process_client_key_exchange(conn, ct, buf, len))
			return -1;
		break;
	case CERTIFICATE_VERIFY:
		if (tls_process_certificate_verify(conn, ct, buf, len))
			return -1;
		break;
	case CHANGE_CIPHER_SPEC:
		if (tls_process_change_cipher_spec(conn, ct, buf, len))
			return -1;
		break;
	case CLIENT_FINISHED:
		if (tls_process_client_finished(conn, ct, buf, len))
			return -1;
		break;
	default:
		tlsv1_server_log(conn, "Unexpected state %d while processing received message",
				 conn->state);
		return -1;
	}

	if (ct == TLS_CONTENT_TYPE_HANDSHAKE)
		tls_verify_hash_add(&conn->verify, buf, *len);

	return 0;
}