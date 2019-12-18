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
struct tls_connection {int ca_cert_verify; int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_NONE ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/ * tls_verify_cb ; 
 int /*<<< orphan*/  wolfSSL_set_accept_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_set_verify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

int tls_connection_set_verify(void *ssl_ctx, struct tls_connection *conn,
			      int verify_peer, unsigned int flags,
			      const u8 *session_ctx, size_t session_ctx_len)
{
	if (!conn)
		return -1;

	wpa_printf(MSG_DEBUG, "SSL: set verify: %d", verify_peer);

	if (verify_peer) {
		conn->ca_cert_verify = 1;
		wolfSSL_set_verify(conn->ssl, SSL_VERIFY_PEER |
				   SSL_VERIFY_FAIL_IF_NO_PEER_CERT,
				   tls_verify_cb);
	} else {
		conn->ca_cert_verify = 0;
		wolfSSL_set_verify(conn->ssl, SSL_VERIFY_NONE, NULL);
	}

	wolfSSL_set_accept_state(conn->ssl);

	/* TODO: do we need to fake a session like OpenSSL does here? */

	return 0;
}