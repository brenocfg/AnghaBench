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
struct TYPE_3__ {int /*<<< orphan*/ * sha1_client; int /*<<< orphan*/ * md5_client; int /*<<< orphan*/ * sha256_client; } ;
struct tlsv1_server {int test_flags; int test_failure_reported; int /*<<< orphan*/  state; scalar_t__ use_session_ticket; int /*<<< orphan*/  master_secret; TYPE_2__ rl; TYPE_1__ verify; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESTABLISHED ; 
 int /*<<< orphan*/  FAILED ; 
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  SERVER_CHANGE_CIPHER_SPEC ; 
 int SHA1_MAC_LEN ; 
 size_t SHA256_MAC_LEN ; 
 int /*<<< orphan*/  TLS_ALERT_DECODE_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_DECRYPT_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  TLS_ALERT_UNEXPECTED_MESSAGE ; 
 int TLS_BREAK_SRV_KEY_X_HASH ; 
 int TLS_BREAK_SRV_KEY_X_SIGNATURE ; 
 scalar_t__ TLS_CONTENT_TYPE_HANDSHAKE ; 
 int TLS_DHE_NON_PRIME ; 
 int TLS_DHE_PRIME_15 ; 
 int TLS_DHE_PRIME_511B ; 
 int TLS_DHE_PRIME_58B ; 
 int TLS_DHE_PRIME_767B ; 
 scalar_t__ const TLS_HANDSHAKE_TYPE_FINISHED ; 
 int /*<<< orphan*/  TLS_MASTER_SECRET_LEN ; 
 int TLS_VERIFY_DATA_LEN ; 
 scalar_t__ TLS_VERSION_1_2 ; 
 size_t WPA_GET_BE24 (scalar_t__ const*) ; 
 scalar_t__ crypto_hash_finish (int /*<<< orphan*/ *,scalar_t__*,size_t*) ; 
 scalar_t__ os_memcmp_const (scalar_t__ const*,scalar_t__*,int) ; 
 scalar_t__ tls_prf (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*,size_t,scalar_t__*,int) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*,...) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tls_process_client_finished(struct tlsv1_server *conn, u8 ct,
				       const u8 *in_data, size_t *in_len)
{
	const u8 *pos, *end;
	size_t left, len, hlen;
	u8 verify_data[TLS_VERIFY_DATA_LEN];
	u8 hash[MD5_MAC_LEN + SHA1_MAC_LEN];

#ifdef CONFIG_TESTING_OPTIONS
	if ((conn->test_flags &
	     (TLS_BREAK_SRV_KEY_X_HASH | TLS_BREAK_SRV_KEY_X_SIGNATURE)) &&
	    !conn->test_failure_reported) {
		tlsv1_server_log(conn, "TEST-FAILURE: Client Finished received after invalid ServerKeyExchange");
		conn->test_failure_reported = 1;
	}

	if ((conn->test_flags & TLS_DHE_PRIME_15) &&
	    !conn->test_failure_reported) {
		tlsv1_server_log(conn, "TEST-FAILURE: Client Finished received after bogus DHE \"prime\" 15");
		conn->test_failure_reported = 1;
	}

	if ((conn->test_flags & TLS_DHE_PRIME_58B) &&
	    !conn->test_failure_reported) {
		tlsv1_server_log(conn, "TEST-FAILURE: Client Finished received after short 58-bit DHE prime in long container");
		conn->test_failure_reported = 1;
	}

	if ((conn->test_flags & TLS_DHE_PRIME_511B) &&
	    !conn->test_failure_reported) {
		tlsv1_server_log(conn, "TEST-WARNING: Client Finished received after short 511-bit DHE prime (insecure)");
		conn->test_failure_reported = 1;
	}

	if ((conn->test_flags & TLS_DHE_PRIME_767B) &&
	    !conn->test_failure_reported) {
		tlsv1_server_log(conn, "TEST-NOTE: Client Finished received after 767-bit DHE prime (relatively insecure)");
		conn->test_failure_reported = 1;
	}

	if ((conn->test_flags & TLS_DHE_NON_PRIME) &&
	    !conn->test_failure_reported) {
		tlsv1_server_log(conn, "TEST-NOTE: Client Finished received after non-prime claimed as DHE prime");
		conn->test_failure_reported = 1;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	if (ct != TLS_CONTENT_TYPE_HANDSHAKE) {
		tlsv1_server_log(conn, "Expected Finished; received content type 0x%x",
				 ct);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	pos = in_data;
	left = *in_len;

	if (left < 4) {
		tlsv1_server_log(conn, "Too short record (left=%lu) forFinished",
				 (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}

	if (pos[0] != TLS_HANDSHAKE_TYPE_FINISHED) {
		wpa_printf(MSG_DEBUG, "TLSv1: Expected Finished; received "
			   "type 0x%x", pos[0]);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_UNEXPECTED_MESSAGE);
		return -1;
	}

	len = WPA_GET_BE24(pos + 1);

	pos += 4;
	left -= 4;

	if (len > left) {
		tlsv1_server_log(conn, "Too short buffer for Finished (len=%lu > left=%lu)",
				 (unsigned long) len, (unsigned long) left);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}
	end = pos + len;
	if (len != TLS_VERIFY_DATA_LEN) {
		tlsv1_server_log(conn, "Unexpected verify_data length in Finished: %lu (expected %d)",
				 (unsigned long) len, TLS_VERIFY_DATA_LEN);
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECODE_ERROR);
		return -1;
	}
	wpa_hexdump(MSG_MSGDUMP, "TLSv1: verify_data in Finished",
		    pos, TLS_VERIFY_DATA_LEN);

#ifdef CONFIG_TLSV12
	if (conn->rl.tls_version >= TLS_VERSION_1_2) {
		hlen = SHA256_MAC_LEN;
		if (conn->verify.sha256_client == NULL ||
		    crypto_hash_finish(conn->verify.sha256_client, hash, &hlen)
		    < 0) {
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			conn->verify.sha256_client = NULL;
			return -1;
		}
		conn->verify.sha256_client = NULL;
	} else {
#endif /* CONFIG_TLSV12 */

	hlen = MD5_MAC_LEN;
	if (conn->verify.md5_client == NULL ||
	    crypto_hash_finish(conn->verify.md5_client, hash, &hlen) < 0) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		conn->verify.md5_client = NULL;
		crypto_hash_finish(conn->verify.sha1_client, NULL, NULL);
		conn->verify.sha1_client = NULL;
		return -1;
	}
	conn->verify.md5_client = NULL;
	hlen = SHA1_MAC_LEN;
	if (conn->verify.sha1_client == NULL ||
	    crypto_hash_finish(conn->verify.sha1_client, hash + MD5_MAC_LEN,
			       &hlen) < 0) {
		conn->verify.sha1_client = NULL;
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	conn->verify.sha1_client = NULL;
	hlen = MD5_MAC_LEN + SHA1_MAC_LEN;

#ifdef CONFIG_TLSV12
	}
#endif /* CONFIG_TLSV12 */

	if (tls_prf(conn->rl.tls_version,
		    conn->master_secret, TLS_MASTER_SECRET_LEN,
		    "client finished", hash, hlen,
		    verify_data, TLS_VERIFY_DATA_LEN)) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to derive verify_data");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_DECRYPT_ERROR);
		return -1;
	}
	wpa_hexdump_key(MSG_DEBUG, "TLSv1: verify_data (client)",
			verify_data, TLS_VERIFY_DATA_LEN);

	if (os_memcmp_const(pos, verify_data, TLS_VERIFY_DATA_LEN) != 0) {
		tlsv1_server_log(conn, "Mismatch in verify_data");
		conn->state = FAILED;
		return -1;
	}

	tlsv1_server_log(conn, "Received Finished");

	*in_len = end - in_data;

	if (conn->use_session_ticket) {
		/* Abbreviated handshake using session ticket; RFC 4507 */
		tlsv1_server_log(conn, "Abbreviated handshake completed successfully");
		conn->state = ESTABLISHED;
	} else {
		/* Full handshake */
		conn->state = SERVER_CHANGE_CIPHER_SPEC;
	}

	return 0;
}