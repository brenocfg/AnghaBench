#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct x509_certificate {int cert_len; int /*<<< orphan*/  issuer; int /*<<< orphan*/  cert_start; } ;
struct TYPE_4__ {int /*<<< orphan*/  cipher_suite; } ;
struct tlsv1_server {int /*<<< orphan*/  verify; TYPE_2__ rl; TYPE_1__* cred; } ;
struct tls_cipher_suite {scalar_t__ key_exchange; } ;
struct TYPE_3__ {struct x509_certificate* cert; int /*<<< orphan*/  trusted_certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  TLS_HANDSHAKE_TYPE_CERTIFICATE ; 
 scalar_t__ TLS_KEY_X_DH_anon ; 
 int TLS_RECORD_HEADER_LEN ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct tls_cipher_suite* tls_get_cipher_suite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_verify_hash_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tlsv1_record_send (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct x509_certificate* x509_certificate_get_subject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ x509_certificate_self_signed (struct x509_certificate*) ; 

__attribute__((used)) static int tls_write_server_certificate(struct tlsv1_server *conn,
					u8 **msgpos, u8 *end)
{
	u8 *pos, *rhdr, *hs_start, *hs_length, *cert_start;
	size_t rlen;
	struct x509_certificate *cert;
	const struct tls_cipher_suite *suite;

	suite = tls_get_cipher_suite(conn->rl.cipher_suite);
	if (suite && suite->key_exchange == TLS_KEY_X_DH_anon) {
		wpa_printf(MSG_DEBUG, "TLSv1: Do not send Certificate when "
			   "using anonymous DH");
		return 0;
	}

	pos = *msgpos;
	if (TLS_RECORD_HEADER_LEN + 1 + 3 + 3 > end - pos) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	tlsv1_server_log(conn, "Send Certificate");
	rhdr = pos;
	pos += TLS_RECORD_HEADER_LEN;

	/* opaque fragment[TLSPlaintext.length] */

	/* Handshake */
	hs_start = pos;
	/* HandshakeType msg_type */
	*pos++ = TLS_HANDSHAKE_TYPE_CERTIFICATE;
	/* uint24 length (to be filled) */
	hs_length = pos;
	pos += 3;
	/* body - Certificate */
	/* uint24 length (to be filled) */
	cert_start = pos;
	pos += 3;
	cert = conn->cred->cert;
	while (cert) {
		if (3 + cert->cert_len > (size_t) (end - pos)) {
			wpa_printf(MSG_DEBUG, "TLSv1: Not enough buffer space "
				   "for Certificate (cert_len=%lu left=%lu)",
				   (unsigned long) cert->cert_len,
				   (unsigned long) (end - pos));
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			return -1;
		}
		WPA_PUT_BE24(pos, cert->cert_len);
		pos += 3;
		os_memcpy(pos, cert->cert_start, cert->cert_len);
		pos += cert->cert_len;

		if (x509_certificate_self_signed(cert))
			break;
		cert = x509_certificate_get_subject(conn->cred->trusted_certs,
						    &cert->issuer);
	}
	if (cert == conn->cred->cert || cert == NULL) {
		/*
		 * Server was not configured with all the needed certificates
		 * to form a full certificate chain. The client may fail to
		 * validate the chain unless it is configured with all the
		 * missing CA certificates.
		 */
		wpa_printf(MSG_DEBUG, "TLSv1: Full server certificate chain "
			   "not configured - validation may fail");
	}
	WPA_PUT_BE24(cert_start, pos - cert_start - 3);

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