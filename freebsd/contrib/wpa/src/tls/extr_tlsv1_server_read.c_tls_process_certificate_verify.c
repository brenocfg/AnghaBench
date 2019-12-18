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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ tls_version; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sha1_cert; int /*<<< orphan*/ * md5_cert; int /*<<< orphan*/ * sha256_cert; } ;
struct tlsv1_server {int /*<<< orphan*/  state; int /*<<< orphan*/  client_rsa_key; TYPE_2__ rl; TYPE_1__ verify; scalar_t__ verify_peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_CIPHER_SPEC ; 
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int SHA1_MAC_LEN ; 
 size_t SHA256_MAC_LEN ; 
 scalar_t__ TLS_ALERT_DECODE_ERROR ; 
 scalar_t__ TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 scalar_t__ TLS_ALERT_UNEXPECTED_MESSAGE ; 
 scalar_t__ TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 scalar_t__ TLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY ; 
 scalar_t__ const TLS_HASH_ALG_SHA256 ; 
 scalar_t__ const TLS_SIGN_ALG_RSA ; 
 scalar_t__ TLS_VERSION_1_2 ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
 scalar_t__ crypto_hash_finish (int /*<<< orphan*/ *,scalar_t__*,size_t*) ; 
 int tls_process_change_cipher_spec (struct tlsv1_server*,scalar_t__,scalar_t__ const*,size_t*) ; 
 scalar_t__ tls_verify_signature (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,size_t,scalar_t__ const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*,...) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static int tls_process_certificate_verify(struct tlsv1_server *conn, u8 ct,
					  const u8 *in_data, size_t *in_len)
{
	const u8 *pos, *end;
	size_t left, len;
	u8 type;
	size_t hlen;
	u8 hash[MD5_MAC_LEN + SHA1_MAC_LEN], *hpos;
	u8 alert;

	if (ct == TLS_CONTENT_TYPE_CHANGE_CIPHER_SPEC) {
		if (conn->verify_peer) {
			tlsv1_server_log(conn, "Client did not include CertificateVerify");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_UNEXPECTED_MESSAGE);
			return -1;
		}

		return tls_process_change_cipher_spec(conn, ct, in_data,
						      in_len);
	}

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
		tlsv1_server_log(conn, "Too short CertificateVerify message (len=%lu)",
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
		tlsv1_server_log(conn, "Unexpected CertificateVerify message length (len=%lu != left=%lu)",
				 (unsigned long) len, (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	end = pos + len;

	if (type != TLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY) {
		tlsv1_server_log(conn, "Received unexpected handshake message %d (expected CertificateVerify)",
				 type);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	tlsv1_server_log(conn, "Received CertificateVerify");

	/*
	 * struct {
	 *   Signature signature;
	 * } CertificateVerify;
	 */

	hpos = hash;

#ifdef CONFIG_TLSV12
	if (conn->rl.tls_version == TLS_VERSION_1_2) {
		/*
		 * RFC 5246, 4.7:
		 * TLS v1.2 adds explicit indication of the used signature and
		 * hash algorithms.
		 *
		 * struct {
		 *   HashAlgorithm hash;
		 *   SignatureAlgorithm signature;
		 * } SignatureAndHashAlgorithm;
		 */
		if (end - pos < 2) {
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_DECODE_ERROR);
			return -1;
		}
		if (pos[0] != TLS_HASH_ALG_SHA256 ||
		    pos[1] != TLS_SIGN_ALG_RSA) {
			wpa_printf(MSG_DEBUG, "TLSv1.2: Unsupported hash(%u)/"
				   "signature(%u) algorithm",
				   pos[0], pos[1]);
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			return -1;
		}
		pos += 2;

		hlen = SHA256_MAC_LEN;
		if (conn->verify.sha256_cert == NULL ||
		    crypto_hash_finish(conn->verify.sha256_cert, hpos, &hlen) <
		    0) {
			conn->verify.sha256_cert = NULL;
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			return -1;
		}
		conn->verify.sha256_cert = NULL;
	} else {
#endif /* CONFIG_TLSV12 */

	hlen = MD5_MAC_LEN;
	if (conn->verify.md5_cert == NULL ||
	    crypto_hash_finish(conn->verify.md5_cert, hpos, &hlen) < 0) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		conn->verify.md5_cert = NULL;
		crypto_hash_finish(conn->verify.sha1_cert, NULL, NULL);
		conn->verify.sha1_cert = NULL;
		return -1;
	}
	hpos += MD5_MAC_LEN;

	conn->verify.md5_cert = NULL;
	hlen = SHA1_MAC_LEN;
	if (conn->verify.sha1_cert == NULL ||
	    crypto_hash_finish(conn->verify.sha1_cert, hpos, &hlen) < 0) {
		conn->verify.sha1_cert = NULL;
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	conn->verify.sha1_cert = NULL;

	hlen += MD5_MAC_LEN;

#ifdef CONFIG_TLSV12
	}
#endif /* CONFIG_TLSV12 */

	wpa_hexdump(MSG_MSGDUMP, "TLSv1: CertificateVerify hash", hash, hlen);

	if (tls_verify_signature(conn->rl.tls_version, conn->client_rsa_key,
				 hash, hlen, pos, end - pos, &alert) < 0) {
		tlsv1_server_log(conn, "Invalid Signature in CertificateVerify");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL, alert);
		return -1;
	}

	*in_len = end - in_data;

	conn->state = CHANGE_CIPHER_SPEC;

	return 0;
}