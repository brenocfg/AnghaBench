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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int u16 ;
struct tlsv1_server {scalar_t__ client_version; TYPE_1__* cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 size_t TLS_PRE_MASTER_SECRET_LEN ; 
 scalar_t__ WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ crypto_private_key_decrypt_pkcs1_v15 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  const* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tlsv1_server_derive_keys (struct tlsv1_server*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*,...) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_process_client_key_exchange_rsa(
	struct tlsv1_server *conn, const u8 *pos, const u8 *end)
{
	u8 *out;
	size_t outlen, outbuflen;
	u16 encr_len;
	int res;
	int use_random = 0;

	if (end - pos < 2) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	encr_len = WPA_GET_BE16(pos);
	pos += 2;
	if (pos + encr_len > end) {
		tlsv1_server_log(conn, "Invalid ClientKeyExchange format: encr_len=%u left=%u",
				 encr_len, (unsigned int) (end - pos));
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	outbuflen = outlen = end - pos;
	out = os_malloc(outlen >= TLS_PRE_MASTER_SECRET_LEN ?
			outlen : TLS_PRE_MASTER_SECRET_LEN);
	if (out == NULL) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	/*
	 * struct {
	 *   ProtocolVersion client_version;
	 *   opaque random[46];
	 * } PreMasterSecret;
	 *
	 * struct {
	 *   public-key-encrypted PreMasterSecret pre_master_secret;
	 * } EncryptedPreMasterSecret;
	 */

	/*
	 * Note: To avoid Bleichenbacher attack, we do not report decryption or
	 * parsing errors from EncryptedPreMasterSecret processing to the
	 * client. Instead, a random pre-master secret is used to force the
	 * handshake to fail.
	 */

	if (crypto_private_key_decrypt_pkcs1_v15(conn->cred->key,
						 pos, encr_len,
						 out, &outlen) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to decrypt "
			   "PreMasterSecret (encr_len=%u outlen=%lu)",
			   encr_len, (unsigned long) outlen);
		use_random = 1;
	}

	if (!use_random && outlen != TLS_PRE_MASTER_SECRET_LEN) {
		tlsv1_server_log(conn, "Unexpected PreMasterSecret length %lu",
				 (unsigned long) outlen);
		use_random = 1;
	}

	if (!use_random && WPA_GET_BE16(out) != conn->client_version) {
		tlsv1_server_log(conn, "Client version in ClientKeyExchange does not match with version in ClientHello");
		use_random = 1;
	}

	if (use_random) {
		wpa_printf(MSG_DEBUG, "TLSv1: Using random premaster secret "
			   "to avoid revealing information about private key");
		outlen = TLS_PRE_MASTER_SECRET_LEN;
		if (os_get_random(out, outlen)) {
			wpa_printf(MSG_DEBUG, "TLSv1: Failed to get random "
				   "data");
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			os_free(out);
			return -1;
		}
	}

	res = tlsv1_server_derive_keys(conn, out, outlen);

	/* Clear the pre-master secret since it is not needed anymore */
	os_memset(out, 0, outbuflen);
	os_free(out);

	if (res) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to derive keys");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	return 0;
}