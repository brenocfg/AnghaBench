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
struct sock {struct chtls_sock* sk_user_data; } ;
struct chtls_sock {struct sock* passive_reap_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct sock* reap_list ; 
 int /*<<< orphan*/  reap_list_lock ; 
 int /*<<< orphan*/  reap_task ; 
 int /*<<< orphan*/  release_tcp_port (struct sock*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_to_reap_list(struct sock *sk)
{
	struct chtls_sock *csk = sk->sk_user_data;

	local_bh_disable();
	bh_lock_sock(sk);
	release_tcp_port(sk); /* release the port immediately */

	spin_lock(&reap_list_lock);
	csk->passive_reap_next = reap_list;
	reap_list = sk;
	if (!csk->passive_reap_next)
		schedule_work(&reap_task);
	spin_unlock(&reap_list_lock);
	bh_unlock_sock(sk);
	local_bh_enable();
}