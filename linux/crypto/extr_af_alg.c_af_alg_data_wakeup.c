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
struct socket_wq {int /*<<< orphan*/  wait; } ;
struct sock {int /*<<< orphan*/  sk_wq; } ;
struct alg_sock {struct af_alg_ctx* private; } ;
struct af_alg_ctx {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int EPOLLOUT ; 
 int EPOLLRDBAND ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SOCK_WAKE_SPACE ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 struct socket_wq* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skwq_has_sleeper (struct socket_wq*) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void af_alg_data_wakeup(struct sock *sk)
{
	struct alg_sock *ask = alg_sk(sk);
	struct af_alg_ctx *ctx = ask->private;
	struct socket_wq *wq;

	if (!ctx->used)
		return;

	rcu_read_lock();
	wq = rcu_dereference(sk->sk_wq);
	if (skwq_has_sleeper(wq))
		wake_up_interruptible_sync_poll(&wq->wait, EPOLLOUT |
							   EPOLLRDNORM |
							   EPOLLRDBAND);
	sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);
	rcu_read_unlock();
}