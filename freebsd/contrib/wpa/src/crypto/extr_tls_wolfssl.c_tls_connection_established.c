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
struct tls_connection {int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 int wolfSSL_is_init_finished (int /*<<< orphan*/ ) ; 

int tls_connection_established(void *tls_ctx, struct tls_connection *conn)
{
	return conn ? wolfSSL_is_init_finished(conn->ssl) : 0;
}