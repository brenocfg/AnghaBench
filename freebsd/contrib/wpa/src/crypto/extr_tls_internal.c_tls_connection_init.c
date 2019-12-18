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
struct tls_global {int /*<<< orphan*/  server_cred; scalar_t__ server; int /*<<< orphan*/  cert_in_cb; int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  event_cb; } ;
struct tls_connection {int /*<<< orphan*/ * server; int /*<<< orphan*/ * client; struct tls_global* global; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct tls_connection*) ; 
 struct tls_connection* os_zalloc (int) ; 
 int /*<<< orphan*/ * tlsv1_client_init () ; 
 int /*<<< orphan*/  tlsv1_client_set_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tlsv1_server_init (int /*<<< orphan*/ ) ; 

struct tls_connection * tls_connection_init(void *tls_ctx)
{
	struct tls_connection *conn;
	struct tls_global *global = tls_ctx;

	conn = os_zalloc(sizeof(*conn));
	if (conn == NULL)
		return NULL;
	conn->global = global;

#ifdef CONFIG_TLS_INTERNAL_CLIENT
	if (!global->server) {
		conn->client = tlsv1_client_init();
		if (conn->client == NULL) {
			os_free(conn);
			return NULL;
		}
		tlsv1_client_set_cb(conn->client, global->event_cb,
				    global->cb_ctx, global->cert_in_cb);
	}
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
#ifdef CONFIG_TLS_INTERNAL_SERVER
	if (global->server) {
		conn->server = tlsv1_server_init(global->server_cred);
		if (conn->server == NULL) {
			os_free(conn);
			return NULL;
		}
	}
#endif /* CONFIG_TLS_INTERNAL_SERVER */

	return conn;
}