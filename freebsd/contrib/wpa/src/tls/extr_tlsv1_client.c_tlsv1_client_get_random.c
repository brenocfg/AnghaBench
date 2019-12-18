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
struct tlsv1_client {scalar_t__ state; int /*<<< orphan*/  server_random; int /*<<< orphan*/  client_random; } ;
struct tls_random {void* server_random_len; int /*<<< orphan*/  server_random; void* client_random_len; int /*<<< orphan*/  client_random; } ;

/* Variables and functions */
 scalar_t__ CLIENT_HELLO ; 
 scalar_t__ SERVER_HELLO ; 
 void* TLS_RANDOM_LEN ; 
 int /*<<< orphan*/  os_memset (struct tls_random*,int /*<<< orphan*/ ,int) ; 

int tlsv1_client_get_random(struct tlsv1_client *conn, struct tls_random *keys)
{
	os_memset(keys, 0, sizeof(*keys));
	if (conn->state == CLIENT_HELLO)
		return -1;

	keys->client_random = conn->client_random;
	keys->client_random_len = TLS_RANDOM_LEN;

	if (conn->state != SERVER_HELLO) {
		keys->server_random = conn->server_random;
		keys->server_random_len = TLS_RANDOM_LEN;
	}

	return 0;
}