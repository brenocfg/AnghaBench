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
typedef  int u8 ;
struct tls_connection {int invalid_hb_used; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 size_t WPA_GET_BE16 (int const*) ; 
 int /*<<< orphan*/  check_server_hello (struct tls_connection*,int const*,int const*) ; 
 int /*<<< orphan*/  check_server_key_exchange (int /*<<< orphan*/ *,struct tls_connection*,int const*,int const*) ; 
 int /*<<< orphan*/  openssl_content_type (int) ; 
 int /*<<< orphan*/  openssl_handshake_type (int,void const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,void const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void tls_msg_cb(int write_p, int version, int content_type,
		       const void *buf, size_t len, SSL *ssl, void *arg)
{
	struct tls_connection *conn = arg;
	const u8 *pos = buf;

	if (write_p == 2) {
		wpa_printf(MSG_DEBUG,
			   "OpenSSL: session ver=0x%x content_type=%d",
			   version, content_type);
		wpa_hexdump_key(MSG_MSGDUMP, "OpenSSL: Data", buf, len);
		return;
	}

	wpa_printf(MSG_DEBUG, "OpenSSL: %s ver=0x%x content_type=%d (%s/%s)",
		   write_p ? "TX" : "RX", version, content_type,
		   openssl_content_type(content_type),
		   openssl_handshake_type(content_type, buf, len));
	wpa_hexdump_key(MSG_MSGDUMP, "OpenSSL: Message", buf, len);
	if (content_type == 24 && len >= 3 && pos[0] == 1) {
		size_t payload_len = WPA_GET_BE16(pos + 1);
		if (payload_len + 3 > len) {
			wpa_printf(MSG_ERROR, "OpenSSL: Heartbeat attack detected");
			conn->invalid_hb_used = 1;
		}
	}

#ifdef CONFIG_SUITEB
	/*
	 * Need to parse these handshake messages to be able to check DH prime
	 * length since OpenSSL does not expose the new cipher suite and DH
	 * parameters during handshake (e.g., for cert_cb() callback).
	 */
	if (content_type == 22 && pos && len > 0 && pos[0] == 2)
		check_server_hello(conn, pos + 1, pos + len);
	if (content_type == 22 && pos && len > 0 && pos[0] == 12)
		check_server_key_exchange(ssl, conn, pos + 1, pos + len);
#endif /* CONFIG_SUITEB */
}