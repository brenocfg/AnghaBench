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
struct tlsv1_client {int (* session_ticket_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  state; int /*<<< orphan*/  rl; int /*<<< orphan*/  session_ticket_cb_ctx; scalar_t__ use_session_ticket; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SERVER_CERTIFICATE ; 
 int /*<<< orphan*/  SERVER_FINISHED ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_ALERT_UNEXPECTED_MESSAGE ; 
 scalar_t__ const TLS_CHANGE_CIPHER_SPEC ; 
 scalar_t__ TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tls_process_certificate (struct tlsv1_client*,scalar_t__,scalar_t__ const*,size_t*) ; 
 scalar_t__ tlsv1_record_change_read_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_process_server_change_cipher_spec(struct tlsv1_client *conn,
						 u8 ct, const u8 *in_data,
						 size_t *in_len)
{
	const u8 *pos;
	size_t left;

	if (ct != TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC) {
		wpa_printf(MSG_DEBUG, "TLSv1: Expected ChangeCipherSpec; "
			   "received content type 0x%x", ct);
		if (conn->use_session_ticket) {
			int res;
			wpa_printf(MSG_DEBUG, "TLSv1: Server may have "
				   "rejected SessionTicket");
			conn->use_session_ticket = 0;

			/* Notify upper layers that SessionTicket failed */
			res = conn->session_ticket_cb(
				conn->session_ticket_cb_ctx, NULL, 0, NULL,
				NULL, NULL);
			if (res < 0) {
				wpa_printf(MSG_DEBUG, "TLSv1: SessionTicket "
					   "callback indicated failure");
				tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
					  TLS_ALERT_HANDSHAKE_FAILURE);
				return -1;
			}

			conn->state = SERVER_CERTIFICATE;
			return tls_process_certificate(conn, ct, in_data,
						       in_len);
		}
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	pos = in_data;
	left = *in_len;

	if (left < 1) {
		wpa_printf(MSG_DEBUG, "TLSv1: Too short ChangeCipherSpec");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL, TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	if (*pos != TLS_CHANGE_CIPHER_SPEC) {
		wpa_printf(MSG_DEBUG, "TLSv1: Expected ChangeCipherSpec; "
			   "received data 0x%x", *pos);
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "TLSv1: Received ChangeCipherSpec");
	if (tlsv1_record_change_read_cipher(&conn->rl) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to change read cipher "
			   "for record layer");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	*in_len = pos + 1 - in_data;

	conn->state = SERVER_FINISHED;

	return 0;
}