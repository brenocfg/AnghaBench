#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drbd_socket {int /*<<< orphan*/  mutex; } ;
struct drbd_peer_device {TYPE_1__* device; int /*<<< orphan*/  connection; } ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;
struct TYPE_2__ {int /*<<< orphan*/  vnr; } ;

/* Variables and functions */
 int __send_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drbd_socket*,int,unsigned int,void*,unsigned int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drbd_send_command(struct drbd_peer_device *peer_device, struct drbd_socket *sock,
		      enum drbd_packet cmd, unsigned int header_size,
		      void *data, unsigned int size)
{
	int err;

	err = __send_command(peer_device->connection, peer_device->device->vnr,
			     sock, cmd, header_size, data, size);
	mutex_unlock(&sock->mutex);
	return err;
}