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
struct tls_connection {int verify_peer; int /*<<< orphan*/ * session; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_CERT_REQUEST ; 
 int /*<<< orphan*/  GNUTLS_CERT_REQUIRE ; 
 int /*<<< orphan*/  gnutls_certificate_server_set_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int tls_connection_set_verify(void *ssl_ctx, struct tls_connection *conn,
			      int verify_peer, unsigned int flags,
			      const u8 *session_ctx, size_t session_ctx_len)
{
	if (conn == NULL || conn->session == NULL)
		return -1;

	conn->verify_peer = verify_peer;
	gnutls_certificate_server_set_request(conn->session,
					      verify_peer ? GNUTLS_CERT_REQUIRE
					      : GNUTLS_CERT_REQUEST);

	return 0;
}