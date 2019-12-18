#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tls_random {int /*<<< orphan*/  server_random_len; int /*<<< orphan*/  client_random_len; int /*<<< orphan*/  server_random; int /*<<< orphan*/  client_random; } ;
struct tls_connection {int /*<<< orphan*/ * session; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ gnutls_datum_t ;

/* Variables and functions */
 int /*<<< orphan*/  gnutls_session_get_random (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  os_memset (struct tls_random*,int /*<<< orphan*/ ,int) ; 

int tls_connection_get_random(void *ssl_ctx, struct tls_connection *conn,
			    struct tls_random *keys)
{
#if GNUTLS_VERSION_NUMBER >= 0x030012
	gnutls_datum_t client, server;

	if (conn == NULL || conn->session == NULL || keys == NULL)
		return -1;

	os_memset(keys, 0, sizeof(*keys));
	gnutls_session_get_random(conn->session, &client, &server);
	keys->client_random = client.data;
	keys->server_random = server.data;
	keys->client_random_len = client.size;
	keys->server_random_len = client.size;

	return 0;
#else /* 3.0.18 */
	return -1;
#endif /* 3.0.18 */
}