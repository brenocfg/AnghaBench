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
 int tlsv1_server_get_failed (scalar_t__) ; 

int tls_connection_get_failed(void *tls_ctx, struct tls_connection *conn)
{
#ifdef CONFIG_TLS_INTERNAL_SERVER
	if (conn->server)
		return tlsv1_server_get_failed(conn->server);
#endif /* CONFIG_TLS_INTERNAL_SERVER */
	return 0;
}