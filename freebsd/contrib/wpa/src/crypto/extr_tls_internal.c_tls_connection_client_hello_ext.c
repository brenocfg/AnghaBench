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
struct tls_connection {scalar_t__ client; } ;

/* Variables and functions */
 int tlsv1_client_hello_ext (scalar_t__,int,int /*<<< orphan*/  const*,size_t) ; 

int tls_connection_client_hello_ext(void *tls_ctx, struct tls_connection *conn,
				    int ext_type, const u8 *data,
				    size_t data_len)
{
#ifdef CONFIG_TLS_INTERNAL_CLIENT
	if (conn->client) {
		return tlsv1_client_hello_ext(conn->client, ext_type,
					      data, data_len);
	}
#endif /* CONFIG_TLS_INTERNAL_CLIENT */
	return -1;
}