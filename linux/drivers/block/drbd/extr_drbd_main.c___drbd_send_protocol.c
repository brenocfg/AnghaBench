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
struct p_protocol {int /*<<< orphan*/  integrity_alg; void* conn_flags; void* two_primaries; void* after_sb_2p; void* after_sb_1p; void* after_sb_0p; void* protocol; } ;
struct net_conf {int wire_protocol; int after_sb_0p; int after_sb_1p; int after_sb_2p; int two_primaries; int /*<<< orphan*/  integrity_alg; scalar_t__ tentative; scalar_t__ discard_my_data; } ;
struct drbd_socket {int dummy; } ;
struct drbd_connection {int agreed_pro_version; int /*<<< orphan*/  net_conf; struct drbd_socket data; } ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;

/* Variables and functions */
 int CF_DISCARD_MY_DATA ; 
 int CF_DRY_RUN ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 struct p_protocol* __conn_prepare_command (struct drbd_connection*,struct drbd_socket*) ; 
 int __conn_send_command (struct drbd_connection*,struct drbd_socket*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*) ; 
 struct net_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int __drbd_send_protocol(struct drbd_connection *connection, enum drbd_packet cmd)
{
	struct drbd_socket *sock;
	struct p_protocol *p;
	struct net_conf *nc;
	int size, cf;

	sock = &connection->data;
	p = __conn_prepare_command(connection, sock);
	if (!p)
		return -EIO;

	rcu_read_lock();
	nc = rcu_dereference(connection->net_conf);

	if (nc->tentative && connection->agreed_pro_version < 92) {
		rcu_read_unlock();
		drbd_err(connection, "--dry-run is not supported by peer");
		return -EOPNOTSUPP;
	}

	size = sizeof(*p);
	if (connection->agreed_pro_version >= 87)
		size += strlen(nc->integrity_alg) + 1;

	p->protocol      = cpu_to_be32(nc->wire_protocol);
	p->after_sb_0p   = cpu_to_be32(nc->after_sb_0p);
	p->after_sb_1p   = cpu_to_be32(nc->after_sb_1p);
	p->after_sb_2p   = cpu_to_be32(nc->after_sb_2p);
	p->two_primaries = cpu_to_be32(nc->two_primaries);
	cf = 0;
	if (nc->discard_my_data)
		cf |= CF_DISCARD_MY_DATA;
	if (nc->tentative)
		cf |= CF_DRY_RUN;
	p->conn_flags    = cpu_to_be32(cf);

	if (connection->agreed_pro_version >= 87)
		strcpy(p->integrity_alg, nc->integrity_alg);
	rcu_read_unlock();

	return __conn_send_command(connection, sock, cmd, size, NULL, 0);
}