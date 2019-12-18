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
typedef  unsigned char u8 ;
struct tls_data {scalar_t__ tls_session_lifetime; } ;
struct tls_connection {int ca_cert_verify; unsigned int flags; int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  counter ;

/* Variables and functions */
 int SSL_VERIFY_CLIENT_ONCE ; 
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_NONE ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_session_id_context (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  SSL_set_verify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ tls_set_conn_flags (struct tls_connection*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tls_verify_cb ; 

int tls_connection_set_verify(void *ssl_ctx, struct tls_connection *conn,
			      int verify_peer, unsigned int flags,
			      const u8 *session_ctx, size_t session_ctx_len)
{
	static int counter = 0;
	struct tls_data *data = ssl_ctx;

	if (conn == NULL)
		return -1;

	if (verify_peer) {
		conn->ca_cert_verify = 1;
		SSL_set_verify(conn->ssl, SSL_VERIFY_PEER |
			       SSL_VERIFY_FAIL_IF_NO_PEER_CERT |
			       SSL_VERIFY_CLIENT_ONCE, tls_verify_cb);
	} else {
		conn->ca_cert_verify = 0;
		SSL_set_verify(conn->ssl, SSL_VERIFY_NONE, NULL);
	}

	if (tls_set_conn_flags(conn, flags, NULL) < 0)
		return -1;
	conn->flags = flags;

	SSL_set_accept_state(conn->ssl);

	if (data->tls_session_lifetime == 0) {
		/*
		 * Set session id context to a unique value to make sure
		 * session resumption cannot be used either through session
		 * caching or TLS ticket extension.
		 */
		counter++;
		SSL_set_session_id_context(conn->ssl,
					   (const unsigned char *) &counter,
					   sizeof(counter));
	} else if (session_ctx) {
		SSL_set_session_id_context(conn->ssl, session_ctx,
					   session_ctx_len);
	}

	return 0;
}