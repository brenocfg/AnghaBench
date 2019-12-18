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
struct tls_connection {scalar_t__ server; } ;

/* Variables and functions */
 int /*<<< orphan*/  tlsv1_server_set_log_cb (scalar_t__,void (*) (void*,char const*),void*) ; 

void tls_connection_set_log_cb(struct tls_connection *conn,
			       void (*log_cb)(void *ctx, const char *msg),
			       void *ctx)
{
#ifdef CONFIG_TLS_INTERNAL_SERVER
	if (conn->server)
		tlsv1_server_set_log_cb(conn->server, log_cb, ctx);
#endif /* CONFIG_TLS_INTERNAL_SERVER */
}