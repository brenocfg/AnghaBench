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
struct tls_random {int dummy; } ;
struct tls_connection {scalar_t__ server; scalar_t__ client; } ;

/* Variables and functions */
 int tlsv1_client_get_random (scalar_t__,struct tls_random*) ; 
 int tlsv1_server_get_random (scalar_t__,struct tls_random*) ; 

int tls_connection_get_random(void *tls_ctx, struct tls_connection *conn,
			      struct tls_random *data)
{
#ifdef CONFIG_TLS_INTERNAL_CLIENT
	if (conn->client)
		return tlsv1_client_get_random(conn->client, data);
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
#ifdef CONFIG_TLS_INTERNAL_SERVER
	if (conn->server)
		return tlsv1_server_get_random(conn->server, data);
#endif /* CONFIG_TLS_INTERNAL_SERVER */
	return -1;
}