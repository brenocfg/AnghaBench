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
struct tls_connection {int /*<<< orphan*/  ssl; scalar_t__ server; } ;

/* Variables and functions */
 size_t SSL_get_finished (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t SSL_get_peer_finished (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int SSL_session_reused (int /*<<< orphan*/ ) ; 

int tls_get_tls_unique(struct tls_connection *conn, u8 *buf, size_t max_len)
{
	size_t len;
	int reused;

	reused = SSL_session_reused(conn->ssl);
	if ((conn->server && !reused) || (!conn->server && reused))
		len = SSL_get_peer_finished(conn->ssl, buf, max_len);
	else
		len = SSL_get_finished(conn->ssl, buf, max_len);

	if (len == 0 || len > max_len)
		return -1;

	return len;
}