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
struct tlsv1_server {int /*<<< orphan*/  verify; int /*<<< orphan*/  rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  TLS_HANDSHAKE_TYPE_CERTIFICATE_STATUS ; 
 int TLS_RECORD_HEADER_LEN ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  tls_verify_hash_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tlsv1_record_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_write_server_certificate_status(struct tlsv1_server *conn,
					       u8 **msgpos, u8 *end,
					       int ocsp_multi,
					       char *ocsp_resp,
					       size_t ocsp_resp_len)
{
	u8 *pos, *rhdr, *hs_start, *hs_length;
	size_t rlen;

	if (!ocsp_resp) {
		 /*
		  * Client did not request certificate status or there is no
		  * matching response cached.
		  */
		return 0;
	}

	pos = *msgpos;
	if (TLS_RECORD_HEADER_LEN + 1 + 3 + 1 + 3 + ocsp_resp_len >
	    (unsigned int) (end - pos)) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	tlsv1_server_log(conn, "Send CertificateStatus (multi=%d)", ocsp_multi);
	rhdr = pos;
	pos += TLS_RECORD_HEADER_LEN;

	/* opaque fragment[TLSPlaintext.length] */

	/* Handshake */
	hs_start = pos;
	/* HandshakeType msg_type */
	*pos++ = TLS_HANDSHAKE_TYPE_CERTIFICATE_STATUS;
	/* uint24 length (to be filled) */
	hs_length = pos;
	pos += 3;

	/* body - CertificateStatus
	 *
	 * struct {
	 *     CertificateStatusType status_type;
	 *     select (status_type) {
	 *         case ocsp: OCSPResponse;
	 *         case ocsp_multi: OCSPResponseList;
	 *     } response;
	 * } CertificateStatus;
	 *
	 * opaque OCSPResponse<1..2^24-1>;
	 *
	 * struct {
	 *   OCSPResponse ocsp_response_list<1..2^24-1>;
	 * } OCSPResponseList;
	 */

	/* CertificateStatusType status_type */
	if (ocsp_multi)
		*pos++ = 2; /* ocsp_multi(2) */
	else
		*pos++ = 1; /* ocsp(1) */
	/* uint24 length of OCSPResponse */
	WPA_PUT_BE24(pos, ocsp_resp_len);
	pos += 3;
	os_memcpy(pos, ocsp_resp, ocsp_resp_len);
	pos += ocsp_resp_len;

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