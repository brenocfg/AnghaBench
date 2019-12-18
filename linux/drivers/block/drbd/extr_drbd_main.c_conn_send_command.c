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
struct drbd_socket {int /*<<< orphan*/  mutex; } ;
struct drbd_connection {int dummy; } ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;

/* Variables and functions */
 int __conn_send_command (struct drbd_connection*,struct drbd_socket*,int,unsigned int,void*,unsigned int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int conn_send_command(struct drbd_connection *connection, struct drbd_socket *sock,
		      enum drbd_packet cmd, unsigned int header_size,
		      void *data, unsigned int size)
{
	int err;

	err = __conn_send_command(connection, sock, cmd, header_size, data, size);
	mutex_unlock(&sock->mutex);
	return err;
}