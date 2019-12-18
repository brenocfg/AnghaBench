#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/ * sha1_cert; int /*<<< orphan*/ * md5_cert; int /*<<< orphan*/ * sha256_cert; } ;
struct TYPE_5__ {scalar_t__ tls_version; } ;
struct tlsv1_client {TYPE_3__ verify; TYPE_2__ rl; TYPE_1__* cred; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 size_t MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 size_t SHA1_MAC_LEN ; 
 size_t SHA256_MAC_LEN ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  TLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY ; 
 int /*<<< orphan*/  TLS_HASH_ALG_SHA256 ; 
 int /*<<< orphan*/  TLS_RECORD_HEADER_LEN ; 
 int /*<<< orphan*/  TLS_SIGN_ALG_RSA ; 
 scalar_t__ TLS_VERSION_1_2 ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ crypto_hash_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ crypto_private_key_sign_pkcs1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  os_memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  tls_alert (struct tlsv1_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_verify_hash_add (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tlsv1_record_send (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_write_client_certificate_verify(struct tlsv1_client *conn,
					       u8 **msgpos, u8 *end)
{
	u8 *pos, *rhdr, *hs_start, *hs_length, *signed_start;
	size_t rlen, hlen, clen;
	u8 hash[100], *hpos;

	pos = *msgpos;

	wpa_printf(MSG_DEBUG, "TLSv1: Send CertificateVerify");
	rhdr = pos;
	pos += TLS_RECORD_HEADER_LEN;

	/* Handshake */
	hs_start = pos;
	/* HandshakeType msg_type */
	*pos++ = TLS_HANDSHAKE_TYPE_CERTIFICATE_VERIFY;
	/* uint24 length (to be filled) */
	hs_length = pos;
	pos += 3;

	/*
	 * RFC 2246: 7.4.3 and 7.4.8:
	 * Signature signature
	 *
	 * RSA:
	 * digitally-signed struct {
	 *     opaque md5_hash[16];
	 *     opaque sha_hash[20];
	 * };
	 *
	 * DSA:
	 * digitally-signed struct {
	 *     opaque sha_hash[20];
	 * };
	 *
	 * The hash values are calculated over all handshake messages sent or
	 * received starting at ClientHello up to, but not including, this
	 * CertificateVerify message, including the type and length fields of
	 * the handshake messages.
	 */

	hpos = hash;

#ifdef CONFIG_TLSV12
	if (conn->rl.tls_version == TLS_VERSION_1_2) {
		hlen = SHA256_MAC_LEN;
		if (conn->verify.sha256_cert == NULL ||
		    crypto_hash_finish(conn->verify.sha256_cert, hpos, &hlen) <
		    0) {
			conn->verify.sha256_cert = NULL;
			tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
				  TLS_ALERT_INTERNAL_ERROR);
			return -1;
		}
		conn->verify.sha256_cert = NULL;

		/*
		 * RFC 3447, A.2.4 RSASSA-PKCS1-v1_5
		 *
		 * DigestInfo ::= SEQUENCE {
		 *   digestAlgorithm DigestAlgorithm,
		 *   digest OCTET STRING
		 * }
		 *
		 * SHA-256 OID: sha256WithRSAEncryption ::= {pkcs-1 11}
		 *
		 * DER encoded DigestInfo for SHA256 per RFC 3447:
		 * 30 31 30 0d 06 09 60 86 48 01 65 03 04 02 01 05 00 04 20 ||
		 * H
		 */
		os_memmove(hash + 19, hash, hlen);
		hlen += 19;
		os_memcpy(hash, "\x30\x31\x30\x0d\x06\x09\x60\x86\x48\x01\x65"
			  "\x03\x04\x02\x01\x05\x00\x04\x20", 19);
	} else {
#endif /* CONFIG_TLSV12 */

	hlen = MD5_MAC_LEN;
	if (conn->verify.md5_cert == NULL ||
	    crypto_hash_finish(conn->verify.md5_cert, hpos, &hlen) < 0) {
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
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
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	conn->verify.sha1_cert = NULL;

	hlen += MD5_MAC_LEN;

#ifdef CONFIG_TLSV12
	}
#endif /* CONFIG_TLSV12 */

	wpa_hexdump(MSG_MSGDUMP, "TLSv1: CertificateVerify hash", hash, hlen);

#ifdef CONFIG_TLSV12
	if (conn->rl.tls_version >= TLS_VERSION_1_2) {
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
		*pos++ = TLS_HASH_ALG_SHA256;
		*pos++ = TLS_SIGN_ALG_RSA;
	}
#endif /* CONFIG_TLSV12 */

	/*
	 * RFC 2246, 4.7:
	 * In digital signing, one-way hash functions are used as input for a
	 * signing algorithm. A digitally-signed element is encoded as an
	 * opaque vector <0..2^16-1>, where the length is specified by the
	 * signing algorithm and key.
	 *
	 * In RSA signing, a 36-byte structure of two hashes (one SHA and one
	 * MD5) is signed (encrypted with the private key). It is encoded with
	 * PKCS #1 block type 0 or type 1 as described in [PKCS1].
	 */
	signed_start = pos; /* length to be filled */
	pos += 2;
	clen = end - pos;
	if (conn->cred == NULL ||
	    crypto_private_key_sign_pkcs1(conn->cred->key, hash, hlen,
					  pos, &clen) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to sign hash (PKCS #1)");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	WPA_PUT_BE16(signed_start, clen);

	pos += clen;

	WPA_PUT_BE24(hs_length, pos - hs_length - 3);

	if (tlsv1_record_send(&conn->rl, TLS_CONTENT_TYPE_HANDSHAKE,
			      rhdr, end - rhdr, hs_start, pos - hs_start,
			      &rlen) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to generate a record");
		tls_alert(conn, TLS_ALERT_LEVEL_FATAL,
			  TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	pos = rhdr + rlen;

	tls_verify_hash_add(&conn->verify, hs_start, pos - hs_start);

	*msgpos = pos;

	return 0;
}