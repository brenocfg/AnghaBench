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

/* Variables and functions */
 void* __conn_prepare_command (struct drbd_connection*,struct drbd_socket*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void *conn_prepare_command(struct drbd_connection *connection, struct drbd_socket *sock)
{
	void *p;

	mutex_lock(&sock->mutex);
	p = __conn_prepare_command(connection, sock);
	if (!p)
		mutex_unlock(&sock->mutex);

	return p;
}