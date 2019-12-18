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
struct tls_connection {scalar_t__ client; } ;

/* Variables and functions */
 int tlsv1_client_get_version (scalar_t__,char*,size_t) ; 

int tls_get_version(void *ssl_ctx, struct tls_connection *conn,
		    char *buf, size_t buflen)
{
	if (conn == NULL)
		return -1;
#ifdef CONFIG_TLS_INTERNAL_CLIENT
	if (conn->client)
		return tlsv1_client_get_version(conn->client, buf, buflen);
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
	return -1;
}