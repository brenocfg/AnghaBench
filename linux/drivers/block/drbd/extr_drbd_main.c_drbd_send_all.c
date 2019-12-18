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
struct socket {int dummy; } ;
struct drbd_connection {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int drbd_send (struct drbd_connection*,struct socket*,void*,size_t,unsigned int) ; 

int drbd_send_all(struct drbd_connection *connection, struct socket *sock, void *buffer,
		  size_t size, unsigned msg_flags)
{
	int err;

	err = drbd_send(connection, sock, buffer, size, msg_flags);
	if (err < 0)
		return err;
	if (err != size)
		return -EIO;
	return 0;
}