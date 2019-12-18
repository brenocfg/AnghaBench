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
typedef  scalar_t__ tls_session_ticket_cb ;
struct tls_connection {int /*<<< orphan*/  ssl; void* session_ticket_cb_ctx; scalar_t__ session_ticket_cb; } ;

/* Variables and functions */
 int SSL_set_session_secret_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tls_connection*) ; 
 int /*<<< orphan*/  SSL_set_session_ticket_ext_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tls_connection*) ; 
 int /*<<< orphan*/ * tls_sess_sec_cb ; 
 int /*<<< orphan*/ * tls_session_ticket_ext_cb ; 

int tls_connection_set_session_ticket_cb(void *tls_ctx,
					 struct tls_connection *conn,
					 tls_session_ticket_cb cb,
					 void *ctx)
{
#ifdef EAP_FAST_OR_TEAP
	conn->session_ticket_cb = cb;
	conn->session_ticket_cb_ctx = ctx;

	if (cb) {
		if (SSL_set_session_secret_cb(conn->ssl, tls_sess_sec_cb,
					      conn) != 1)
			return -1;
		SSL_set_session_ticket_ext_cb(conn->ssl,
					      tls_session_ticket_ext_cb, conn);
	} else {
		if (SSL_set_session_secret_cb(conn->ssl, NULL, NULL) != 1)
			return -1;
		SSL_set_session_ticket_ext_cb(conn->ssl, NULL, NULL);
	}

	return 0;
#else /* EAP_FAST_OR_TEAP */
	return -1;
#endif /* EAP_FAST_OR_TEAP */
}