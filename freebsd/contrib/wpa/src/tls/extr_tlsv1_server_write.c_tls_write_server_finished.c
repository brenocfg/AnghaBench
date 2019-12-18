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
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ tls_version; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sha1_server; int /*<<< orphan*/ * md5_server; int /*<<< orphan*/ * sha256_server; } ;
struct tlsv1_server {int test_flags; TYPE_1__ rl; TYPE_2__ verify; int /*<<< orphan*/  master_secret; } ;

/* Variables and functions */
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA1_MAC_LEN ; 
 size_t SHA256_MAC_LEN ; 
 int /*<<< orphan*/  TLS_ALERT_INTERNAL_ERROR ; 
 int /*<<< orphan*/  TLS_ALERT_LEVEL_FATAL ; 
 int TLS_BREAK_VERIFY_DATA ; 
 int /*<<< orphan*/  TLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  TLS_HANDSHAKE_TYPE_FINISHED ; 
 int /*<<< orphan*/  TLS_MASTER_SECRET_LEN ; 
 int TLS_VERIFY_DATA_LEN ; 
 scalar_t__ TLS_VERSION_1_2 ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int*,int) ; 
 scalar_t__ crypto_hash_finish (int /*<<< orphan*/ *,int*,size_t*) ; 
 scalar_t__ tls_prf (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,size_t,int*,int) ; 
 int /*<<< orphan*/  tls_verify_hash_add (TYPE_2__*,int*,int) ; 
 scalar_t__ tlsv1_record_send (TYPE_1__*,int /*<<< orphan*/ ,int*,int,int*,int,size_t*) ; 
 int /*<<< orphan*/  tlsv1_server_alert (struct tlsv1_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlsv1_server_log (struct tlsv1_server*,char*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_write_server_finished(struct tlsv1_server *conn,
				     u8 **msgpos, u8 *end)
{
	u8 *pos, *hs_start;
	size_t rlen, hlen;
	u8 verify_data[1 + 3 + TLS_VERIFY_DATA_LEN];
	u8 hash[MD5_MAC_LEN + SHA1_MAC_LEN];

	pos = *msgpos;

	tlsv1_server_log(conn, "Send Finished");

	/* Encrypted Handshake Message: Finished */

#ifdef CONFIG_TLSV12
	if (conn->rl.tls_version >= TLS_VERSION_1_2) {
		hlen = SHA256_MAC_LEN;
		if (conn->verify.sha256_server == NULL ||
		    crypto_hash_finish(conn->verify.sha256_server, hash, &hlen)
		    < 0) {
			conn->verify.sha256_server = NULL;
			tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
					   TLS_ALERT_INTERNAL_ERROR);
			return -1;
		}
		conn->verify.sha256_server = NULL;
	} else {
#endif /* CONFIG_TLSV12 */

	hlen = MD5_MAC_LEN;
	if (conn->verify.md5_server == NULL ||
	    crypto_hash_finish(conn->verify.md5_server, hash, &hlen) < 0) {
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		conn->verify.md5_server = NULL;
		crypto_hash_finish(conn->verify.sha1_server, NULL, NULL);
		conn->verify.sha1_server = NULL;
		return -1;
	}
	conn->verify.md5_server = NULL;
	hlen = SHA1_MAC_LEN;
	if (conn->verify.sha1_server == NULL ||
	    crypto_hash_finish(conn->verify.sha1_server, hash + MD5_MAC_LEN,
			       &hlen) < 0) {
		conn->verify.sha1_server = NULL;
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	conn->verify.sha1_server = NULL;
	hlen = MD5_MAC_LEN + SHA1_MAC_LEN;

#ifdef CONFIG_TLSV12
	}
#endif /* CONFIG_TLSV12 */

	if (tls_prf(conn->rl.tls_version,
		    conn->master_secret, TLS_MASTER_SECRET_LEN,
		    "server finished", hash, hlen,
		    verify_data + 1 + 3, TLS_VERIFY_DATA_LEN)) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to generate verify_data");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}
	wpa_hexdump_key(MSG_DEBUG, "TLSv1: verify_data (server)",
			verify_data + 1 + 3, TLS_VERIFY_DATA_LEN);
#ifdef CONFIG_TESTING_OPTIONS
	if (conn->test_flags & TLS_BREAK_VERIFY_DATA) {
		tlsv1_server_log(conn, "TESTING: Break verify_data (server)");
		verify_data[1 + 3 + 1] ^= 0x80;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	/* Handshake */
	pos = hs_start = verify_data;
	/* HandshakeType msg_type */
	*pos++ = TLS_HANDSHAKE_TYPE_FINISHED;
	/* uint24 length */
	WPA_PUT_BE24(pos, TLS_VERIFY_DATA_LEN);
	pos += 3;
	pos += TLS_VERIFY_DATA_LEN;
	tls_verify_hash_add(&conn->verify, hs_start, pos - hs_start);

	if (tlsv1_record_send(&conn->rl, TLS_CONTENT_TYPE_HANDSHAKE,
			      *msgpos, end - *msgpos, hs_start, pos - hs_start,
			      &rlen) < 0) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to create a record");
		tlsv1_server_alert(conn, TLS_ALERT_LEVEL_FATAL,
				   TLS_ALERT_INTERNAL_ERROR);
		return -1;
	}

	*msgpos += rlen;

	return 0;
}