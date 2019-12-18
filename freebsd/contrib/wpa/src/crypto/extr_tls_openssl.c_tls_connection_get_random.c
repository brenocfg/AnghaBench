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
struct tls_random {int /*<<< orphan*/  server_random_len; int /*<<< orphan*/  server_random; int /*<<< orphan*/  client_random_len; int /*<<< orphan*/  client_random; } ;
struct tls_connection {int /*<<< orphan*/  server_random; int /*<<< orphan*/  client_random; int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_get_client_random (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_get_server_random (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memset (struct tls_random*,int /*<<< orphan*/ ,int) ; 

int tls_connection_get_random(void *ssl_ctx, struct tls_connection *conn,
			      struct tls_random *keys)
{
	SSL *ssl;

	if (conn == NULL || keys == NULL)
		return -1;
	ssl = conn->ssl;
	if (ssl == NULL)
		return -1;

	os_memset(keys, 0, sizeof(*keys));
	keys->client_random = conn->client_random;
	keys->client_random_len = SSL_get_client_random(
		ssl, conn->client_random, sizeof(conn->client_random));
	keys->server_random = conn->server_random;
	keys->server_random_len = SSL_get_server_random(
		ssl, conn->server_random, sizeof(conn->server_random));

	return 0;
}