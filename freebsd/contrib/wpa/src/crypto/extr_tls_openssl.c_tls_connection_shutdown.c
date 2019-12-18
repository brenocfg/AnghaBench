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
struct tls_connection {int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int SSL_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_quiet_shutdown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ ) ; 

int tls_connection_shutdown(void *ssl_ctx, struct tls_connection *conn)
{
	if (conn == NULL)
		return -1;

	/* Shutdown previous TLS connection without notifying the peer
	 * because the connection was already terminated in practice
	 * and "close notify" shutdown alert would confuse AS. */
	SSL_set_quiet_shutdown(conn->ssl, 1);
	SSL_shutdown(conn->ssl);
	return SSL_clear(conn->ssl) == 1 ? 0 : -1;
}