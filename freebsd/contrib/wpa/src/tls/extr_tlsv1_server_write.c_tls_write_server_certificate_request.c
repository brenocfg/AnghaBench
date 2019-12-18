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
struct tlsv1_server {int /*<<< orphan*/  verify; int /*<<< orphan*/  rl; int /*<<< orphan*/  verify_peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  TLS_HANDSHAKE_TYPE_CERTIFICATE_REQUEST ; 
 int /*<<< orphan*/  TLS_RECORD_HEADER_LEN ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_verify_hash_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tlsv1_record_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_write_server_certificate_request(struct tlsv1_server *conn,
						u8 **msgpos, u8 *end)
{
	u8 *pos, *rhdr, *hs_start, *hs_length;
	size_t rlen;

	if (!conn->verify_peer) {
		wpa_printf(MSG_DEBUG, "TLSv1: No CertificateRequest needed");
		return 0;
	}

	pos = *msgpos;

	tlsv1_server_log(conn, "Send CertificateRequest");
	rhdr = pos;
	pos += TLS_RECORD_HEADER_LEN;

	/* opaque fragment[TLSPlaintext.length] */

	/* Handshake */
	hs_start = pos;
	/* HandshakeType msg_type */
	*pos++ = TLS_HANDSHAKE_TYPE_CERTIFICATE_REQUEST;
	/* uint24 length (to be filled) */
	hs_length = pos;
	pos += 3;
	/* body - CertificateRequest */

	/*
	 * enum {
	 *   rsa_sign(1), dss_sign(2), rsa_fixed_dh(3), dss_fixed_dh(4),
	 *   (255)
	 * } ClientCertificateType;
	 * ClientCertificateType certificate_types<1..2^8-1>
	 */
	*pos++ = 1;
	*pos++ = 1; /* rsa_sign */

	/*
	 * opaque DistinguishedName<1..2^16-1>
	 * DistinguishedName certificate_authorities<3..2^16-1>
	 */
	/* TODO: add support for listing DNs for trusted CAs */
	WPA_PUT_BE16(pos, 0);
	pos += 2;

	WPA_PUT_BE24(hs_length, pos - hs_length - 3);

	if (tlsv1_record_send(&conn->rl, TLS_CONTENT_TYPE_HANDSHAKE,
			      rhdr, end - rhdr, hs_start, pos - hs_start,
			      &rlen) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to generate a record");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	pos = rhdr + rlen;

	tls_verify_hash_add(&conn->verify, hs_start, pos - hs_start);

	*msgpos = pos;

	return 0;
}