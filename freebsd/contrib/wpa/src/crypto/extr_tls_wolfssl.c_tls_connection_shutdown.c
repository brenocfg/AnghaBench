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
typedef  int /*<<< orphan*/  WOLFSSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int wolfSSL_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wolfSSL_get_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_set_quiet_shutdown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wolfSSL_set_session (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int tls_connection_shutdown(void *tls_ctx, struct tls_connection *conn)
{
	WOLFSSL_SESSION *session;

	if (!conn)
		return -1;

	wpa_printf(MSG_DEBUG, "SSL: connection shutdown");

	/* Set quiet as OpenSSL does */
	wolfSSL_set_quiet_shutdown(conn->ssl, 1);
	wolfSSL_shutdown(conn->ssl);

	session = wolfSSL_get_session(conn->ssl);
	if (wolfSSL_clear(conn->ssl) != 1)
		return -1;
	wolfSSL_set_session(conn->ssl, session);

	return 0;
}