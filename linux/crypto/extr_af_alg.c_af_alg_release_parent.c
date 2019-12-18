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
struct sock {int dummy; } ;
struct alg_sock {unsigned int nokey_refcnt; int /*<<< orphan*/  refcnt; struct sock* parent; } ;

/* Variables and functions */
 struct alg_sock* alg_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

void af_alg_release_parent(struct sock *sk)
{
	struct alg_sock *ask = alg_sk(sk);
	unsigned int nokey = ask->nokey_refcnt;
	bool last = nokey && !ask->refcnt;

	sk = ask->parent;
	ask = alg_sk(sk);

	lock_sock(sk);
	ask->nokey_refcnt -= nokey;
	if (!last)
		last = !--ask->refcnt;
	release_sock(sk);

	if (last)
		sock_put(sk);
}