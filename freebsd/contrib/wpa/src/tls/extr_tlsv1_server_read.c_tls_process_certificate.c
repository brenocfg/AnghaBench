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
struct x509_certificate {int extensions_present; int ext_key_usage; struct x509_certificate* next; } ;
struct tlsv1_server {int /*<<< orphan*/  state; TYPE_1__* cred; int /*<<< orphan*/  client_rsa_key; scalar_t__ verify_peer; } ;
struct TYPE_2__ {int /*<<< orphan*/  trusted_certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_KEY_EXCHANGE ; 
 int TLS_ALERT_BAD_CERTIFICATE ; 
 int TLS_ALERT_CERTIFICATE_EXPIRED ; 
 int TLS_ALERT_CERTIFICATE_REVOKED ; 
 int TLS_ALERT_CERTIFICATE_UNKNOWN ; 
 int TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int TLS_ALERT_UNEXPECTED_MESSAGE ; 
 int TLS_ALERT_UNKNOWN_CA ; 
 int TLS_ALERT_UNSUPPORTED_CERTIFICATE ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CERTIFICATE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CLIENT_KEY_EXCHANGE ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
 int X509_EXT_EXT_KEY_USAGE ; 
 int X509_EXT_KEY_USAGE_ANY ; 
 int X509_EXT_KEY_USAGE_CLIENT_AUTH ; 
#define  X509_VALIDATE_BAD_CERTIFICATE 133 
#define  X509_VALIDATE_CERTIFICATE_EXPIRED 132 
#define  X509_VALIDATE_CERTIFICATE_REVOKED 131 
#define  X509_VALIDATE_CERTIFICATE_UNKNOWN 130 
#define  X509_VALIDATE_UNKNOWN_CA 129 
#define  X509_VALIDATE_UNSUPPORTED_CERTIFICATE 128 
 int /*<<< orphan*/  crypto_public_key_free (int /*<<< orphan*/ ) ; 
 scalar_t__ tls_parse_cert (scalar_t__ const*,size_t,int /*<<< orphan*/ *) ; 
 int tls_process_client_key_exchange (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*,...) ; 
 int /*<<< orphan*/  x509_certificate_chain_free (struct x509_certificate*) ; 
 scalar_t__ x509_certificate_chain_validate (int /*<<< orphan*/ ,struct x509_certificate*,int*,int /*<<< orphan*/ ) ; 
 struct x509_certificate* x509_certificate_parse (scalar_t__ const*,size_t) ; 

__attribute__((used)) static int tls_process_certificate(struct tlsv1_server *conn, u8 ct,
				   const u8 *in_data, size_t *in_len)
{
	const u8 *pos, *end;
	size_t left, len, list_len, cert_len, idx;
	u8 type;
	struct x509_certificate *chain = NULL, *last = NULL, *cert;
	int reason;

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
		tlsv1_server_log(conn, "Too short Certificate message (len=%lu)",
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
		tlsv1_server_log(conn, "Unexpected Certificate message length (len=%lu != left=%lu)",
				 (unsigned long) len, (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	if (type == TLS_HANDSHAKE_TYPE_CLIENT_KEY_EXCHANGE) {
		if (conn->verify_peer) {
			tlsv1_server_log(conn, "Client did not include Certificate");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_UNEXPECTED_MESSAGE);
			return -1;
		}

		return tls_process_client_key_exchange(conn, ct, in_data,
						       in_len);
	}
	if (type != TLS_HANDSHAKE_TYPE_CERTIFICATE) {
		tlsv1_server_log(conn, "Received unexpected handshake message %d (expected Certificate/ClientKeyExchange)",
				 type);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	tlsv1_server_log(conn, "Received Certificate (certificate_list len %lu)",
			 (unsigned long) len);

	/*
	 * opaque ASN.1Cert<2^24-1>;
	 *
	 * struct {
	 *     ASN.1Cert certificate_list<1..2^24-1>;
	 * } Certificate;
	 */

	end = pos + len;

	if (end - pos < 3) {
		tlsv1_server_log(conn, "Too short Certificate (left=%lu)",
				 (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	list_len = WPA_GET_BE24(pos);
	pos += 3;

	if ((size_t) (end - pos) != list_len) {
		tlsv1_server_log(conn, "Unexpected certificate_list length (len=%lu left=%lu)",
				 (unsigned long) list_len,
				 (unsigned long) (end - pos));
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	idx = 0;
	while (pos < end) {
		if (end - pos < 3) {
			tlsv1_server_log(conn, "Failed to parse certificate_list");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_DECODE_ERROR);
			x509_certificate_chain_free(chain);
			return -1;
		}

		cert_len = WPA_GET_BE24(pos);
		pos += 3;

		if ((size_t) (end - pos) < cert_len) {
			tlsv1_server_log(conn, "Unexpected certificate length (len=%lu left=%lu)",
					 (unsigned long) cert_len,
					 (unsigned long) (end - pos));
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_DECODE_ERROR);
			x509_certificate_chain_free(chain);
			return -1;
		}

		tlsv1_server_log(conn, "Certificate %lu (len %lu)",
				 (unsigned long) idx, (unsigned long) cert_len);

		if (idx == 0) {
			crypto_public_key_free(conn->client_rsa_key);
			if (tls_parse_cert(pos, cert_len,
					   &conn->client_rsa_key)) {
				tlsv1_server_log(conn, "Failed to parse the certificate");
				tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
						   TLS_ALERT_BAD_CERTIFICATE);
				x509_certificate_chain_free(chain);
				return -1;
			}
		}

		cert = x509_certificate_parse(pos, cert_len);
		if (cert == NULL) {
			tlsv1_server_log(conn, "Failed to parse the certificate");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_BAD_CERTIFICATE);
			x509_certificate_chain_free(chain);
			return -1;
		}

		if (last == NULL)
			chain = cert;
		else
			last->next = cert;
		last = cert;

		idx++;
		pos += cert_len;
	}

	if (x509_certificate_chain_validate(conn->cred->trusted_certs, chain,
					    &reason, 0) < 0) {
		int tls_reason;
		tlsv1_server_log(conn, "Server certificate chain validation failed (reason=%d)",
				 reason);
		switch (reason) {
		case X509_VALIDATE_BAD_CERTIFICATE:
			tls_reason = TLS_ALERT_BAD_CERTIFICATE;
			break;
		case X509_VALIDATE_UNSUPPORTED_CERTIFICATE:
			tls_reason = TLS_ALERT_UNSUPPORTED_CERTIFICATE;
			break;
		case X509_VALIDATE_CERTIFICATE_REVOKED:
			tls_reason = TLS_ALERT_CERTIFICATE_REVOKED;
			break;
		case X509_VALIDATE_CERTIFICATE_EXPIRED:
			tls_reason = TLS_ALERT_CERTIFICATE_EXPIRED;
			break;
		case X509_VALIDATE_CERTIFICATE_UNKNOWN:
			tls_reason = TLS_ALERT_CERTIFICATE_UNKNOWN;
			break;
		case X509_VALIDATE_UNKNOWN_CA:
			tls_reason = TLS_ALERT_UNKNOWN_CA;
			break;
		default:
			tls_reason = TLS_ALERT_BAD_CERTIFICATE;
			break;
		}
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL, tls_reason);
		x509_certificate_chain_free(chain);
		return -1;
	}

	if (chain && (chain->extensions_present & X509_EXT_EXT_KEY_USAGE) &&
	    !(chain->ext_key_usage &
	      (X509_EXT_KEY_USAGE_ANY | X509_EXT_KEY_USAGE_CLIENT_AUTH))) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_BAD_CERTIFICATE);
		x509_certificate_chain_free(chain);
		return -1;
	}

	x509_certificate_chain_free(chain);

	*in_len = end - in_data;

	conn->state = CLIENT_KEY_EXCHANGE;

	return 0;
}