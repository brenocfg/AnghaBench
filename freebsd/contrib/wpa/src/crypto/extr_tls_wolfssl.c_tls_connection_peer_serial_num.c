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
struct tls_connection {int dummy; } ;

/* Variables and functions */

char * tls_connection_peer_serial_num(void *tls_ctx,
				      struct tls_connection *conn)
{
	/* TODO */
	return NULL;
}