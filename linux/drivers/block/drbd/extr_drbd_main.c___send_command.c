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
struct drbd_socket {void* sbuf; int /*<<< orphan*/  socket; } ;
struct drbd_connection {int dummy; } ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;

/* Variables and functions */
 int MSG_MORE ; 
 int P_PING ; 
 int P_PING_ACK ; 
 int drbd_send_all (struct drbd_connection*,int /*<<< orphan*/ ,void*,unsigned int,int) ; 
 int /*<<< orphan*/  drbd_tcp_nodelay (int /*<<< orphan*/ ) ; 
 scalar_t__ prepare_header (struct drbd_connection*,int,void*,int,unsigned int) ; 

__attribute__((used)) static int __send_command(struct drbd_connection *connection, int vnr,
			  struct drbd_socket *sock, enum drbd_packet cmd,
			  unsigned int header_size, void *data,
			  unsigned int size)
{
	int msg_flags;
	int err;

	/*
	 * Called with @data == NULL and the size of the data blocks in @size
	 * for commands that send data blocks.  For those commands, omit the
	 * MSG_MORE flag: this will increase the likelihood that data blocks
	 * which are page aligned on the sender will end up page aligned on the
	 * receiver.
	 */
	msg_flags = data ? MSG_MORE : 0;

	header_size += prepare_header(connection, vnr, sock->sbuf, cmd,
				      header_size + size);
	err = drbd_send_all(connection, sock->socket, sock->sbuf, header_size,
			    msg_flags);
	if (data && !err)
		err = drbd_send_all(connection, sock->socket, data, size, 0);
	/* DRBD protocol "pings" are latency critical.
	 * This is supposed to trigger tcp_push_pending_frames() */
	if (!err && (cmd == P_PING || cmd == P_PING_ACK))
		drbd_tcp_nodelay(sock->socket);

	return err;
}