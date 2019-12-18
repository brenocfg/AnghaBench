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
struct tls_connection {int /*<<< orphan*/  ssl; int /*<<< orphan*/  context; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  WOLFSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (struct tls_connection*) ; 
 struct tls_connection* os_zalloc (int) ; 
 int /*<<< orphan*/  wolfSSL_CTX_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_KeepArrays (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_KeepHandshakeResources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_SetIOReadCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_SetIOWriteCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_UseClientSuites (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_set_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tls_connection*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct tls_connection * tls_connection_init(void *tls_ctx)
{
	WOLFSSL_CTX *ssl_ctx = tls_ctx;
	struct tls_connection *conn;

	wpa_printf(MSG_DEBUG, "SSL: connection init");

	conn = os_zalloc(sizeof(*conn));
	if (!conn)
		return NULL;
	conn->ssl = wolfSSL_new(ssl_ctx);
	if (!conn->ssl) {
		os_free(conn);
		return NULL;
	}

	wolfSSL_SetIOReadCtx(conn->ssl,  &conn->input);
	wolfSSL_SetIOWriteCtx(conn->ssl, &conn->output);
	wolfSSL_set_ex_data(conn->ssl, 0, conn);
	conn->context = wolfSSL_CTX_get_ex_data(ssl_ctx, 0);

	/* Need randoms post-hanshake for EAP-FAST, export key and deriving
	 * session ID in EAP methods. */
	wolfSSL_KeepArrays(conn->ssl);
	wolfSSL_KeepHandshakeResources(conn->ssl);
	wolfSSL_UseClientSuites(conn->ssl);

	return conn;
}