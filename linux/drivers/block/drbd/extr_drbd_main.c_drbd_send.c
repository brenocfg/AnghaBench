#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct msghdr {unsigned int msg_flags; int /*<<< orphan*/  msg_iter; } ;
struct kvec {void* iov_base; size_t iov_len; } ;
struct TYPE_5__ {struct socket* socket; } ;
struct TYPE_4__ {struct socket* socket; } ;
struct drbd_connection {TYPE_2__ meta; int /*<<< orphan*/  flags; TYPE_1__ data; int /*<<< orphan*/  net_conf; int /*<<< orphan*/  ko_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  ko_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_HARD ; 
 int /*<<< orphan*/  C_BROKEN_PIPE ; 
 int /*<<< orphan*/  C_TIMEOUT ; 
 int EAGAIN ; 
 int EBADR ; 
 int EINTR ; 
 unsigned int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  NET_CONGESTED ; 
 int /*<<< orphan*/  NS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  conn_request_state (struct drbd_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*,char*,int) ; 
 int /*<<< orphan*/  drbd_update_congested (struct drbd_connection*) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,size_t) ; 
 TYPE_3__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int sock_sendmsg (struct socket*,struct msghdr*) ; 
 scalar_t__ we_should_drop_the_connection (struct drbd_connection*,struct socket*) ; 

int drbd_send(struct drbd_connection *connection, struct socket *sock,
	      void *buf, size_t size, unsigned msg_flags)
{
	struct kvec iov = {.iov_base = buf, .iov_len = size};
	struct msghdr msg = {.msg_flags = msg_flags | MSG_NOSIGNAL};
	int rv, sent = 0;

	if (!sock)
		return -EBADR;

	/* THINK  if (signal_pending) return ... ? */

	iov_iter_kvec(&msg.msg_iter, WRITE, &iov, 1, size);

	if (sock == connection->data.socket) {
		rcu_read_lock();
		connection->ko_count = rcu_dereference(connection->net_conf)->ko_count;
		rcu_read_unlock();
		drbd_update_congested(connection);
	}
	do {
		rv = sock_sendmsg(sock, &msg);
		if (rv == -EAGAIN) {
			if (we_should_drop_the_connection(connection, sock))
				break;
			else
				continue;
		}
		if (rv == -EINTR) {
			flush_signals(current);
			rv = 0;
		}
		if (rv < 0)
			break;
		sent += rv;
	} while (sent < size);

	if (sock == connection->data.socket)
		clear_bit(NET_CONGESTED, &connection->flags);

	if (rv <= 0) {
		if (rv != -EAGAIN) {
			drbd_err(connection, "%s_sendmsg returned %d\n",
				 sock == connection->meta.socket ? "msock" : "sock",
				 rv);
			conn_request_state(connection, NS(conn, C_BROKEN_PIPE), CS_HARD);
		} else
			conn_request_state(connection, NS(conn, C_TIMEOUT), CS_HARD);
	}

	return sent;
}