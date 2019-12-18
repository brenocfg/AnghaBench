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
struct socket {int /*<<< orphan*/  sk; } ;
struct net_conf {int connect_int; } ;
struct drbd_connection {int /*<<< orphan*/  net_conf; } ;
struct accept_wait_data {int /*<<< orphan*/  s_listen; int /*<<< orphan*/  door_bell; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_HARD ; 
 int /*<<< orphan*/  C_DISCONNECTING ; 
 int EAGAIN ; 
 int EINTR ; 
 int ERESTARTSYS ; 
 int HZ ; 
 int /*<<< orphan*/  NS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  conn_request_state (struct drbd_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*,int) ; 
 int kernel_accept (int /*<<< orphan*/ ,struct socket**,int /*<<< orphan*/ ) ; 
 int prandom_u32 () ; 
 struct net_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  unregister_state_change (int /*<<< orphan*/ ,struct accept_wait_data*) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct socket *drbd_wait_for_connect(struct drbd_connection *connection, struct accept_wait_data *ad)
{
	int timeo, connect_int, err = 0;
	struct socket *s_estab = NULL;
	struct net_conf *nc;

	rcu_read_lock();
	nc = rcu_dereference(connection->net_conf);
	if (!nc) {
		rcu_read_unlock();
		return NULL;
	}
	connect_int = nc->connect_int;
	rcu_read_unlock();

	timeo = connect_int * HZ;
	/* 28.5% random jitter */
	timeo += (prandom_u32() & 1) ? timeo / 7 : -timeo / 7;

	err = wait_for_completion_interruptible_timeout(&ad->door_bell, timeo);
	if (err <= 0)
		return NULL;

	err = kernel_accept(ad->s_listen, &s_estab, 0);
	if (err < 0) {
		if (err != -EAGAIN && err != -EINTR && err != -ERESTARTSYS) {
			drbd_err(connection, "accept failed, err = %d\n", err);
			conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_HARD);
		}
	}

	if (s_estab)
		unregister_state_change(s_estab->sk, ad);

	return s_estab;
}