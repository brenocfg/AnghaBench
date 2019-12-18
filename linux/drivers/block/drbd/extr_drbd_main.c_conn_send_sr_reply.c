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
struct p_req_state_reply {int /*<<< orphan*/  retcode; } ;
struct drbd_socket {int dummy; } ;
struct drbd_connection {int agreed_pro_version; struct drbd_socket meta; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;

/* Variables and functions */
 int P_CONN_ST_CHG_REPLY ; 
 int P_STATE_CHG_REPLY ; 
 struct p_req_state_reply* conn_prepare_command (struct drbd_connection*,struct drbd_socket*) ; 
 int /*<<< orphan*/  conn_send_command (struct drbd_connection*,struct drbd_socket*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

void conn_send_sr_reply(struct drbd_connection *connection, enum drbd_state_rv retcode)
{
	struct drbd_socket *sock;
	struct p_req_state_reply *p;
	enum drbd_packet cmd = connection->agreed_pro_version < 100 ? P_STATE_CHG_REPLY : P_CONN_ST_CHG_REPLY;

	sock = &connection->meta;
	p = conn_prepare_command(connection, sock);
	if (p) {
		p->retcode = cpu_to_be32(retcode);
		conn_send_command(connection, sock, cmd, sizeof(*p), NULL, 0);
	}
}