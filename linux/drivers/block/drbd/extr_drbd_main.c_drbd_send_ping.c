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
struct drbd_socket {int dummy; } ;
struct drbd_connection {struct drbd_socket meta; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  P_PING ; 
 int /*<<< orphan*/  conn_prepare_command (struct drbd_connection*,struct drbd_socket*) ; 
 int conn_send_command (struct drbd_connection*,struct drbd_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int drbd_send_ping(struct drbd_connection *connection)
{
	struct drbd_socket *sock;

	sock = &connection->meta;
	if (!conn_prepare_command(connection, sock))
		return -EIO;
	return conn_send_command(connection, sock, P_PING, 0, NULL, 0);
}