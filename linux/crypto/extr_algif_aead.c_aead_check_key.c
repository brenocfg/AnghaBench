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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct alg_sock {int refcnt; struct aead_tfm* private; struct sock* parent; } ;
struct aead_tfm {int /*<<< orphan*/  aead; } ;

/* Variables and functions */
 int CRYPTO_TFM_NEED_KEY ; 
 int ENOKEY ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 int crypto_aead_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int aead_check_key(struct socket *sock)
{
	int err = 0;
	struct sock *psk;
	struct alg_sock *pask;
	struct aead_tfm *tfm;
	struct sock *sk = sock->sk;
	struct alg_sock *ask = alg_sk(sk);

	lock_sock(sk);
	if (ask->refcnt)
		goto unlock_child;

	psk = ask->parent;
	pask = alg_sk(ask->parent);
	tfm = pask->private;

	err = -ENOKEY;
	lock_sock_nested(psk, SINGLE_DEPTH_NESTING);
	if (crypto_aead_get_flags(tfm->aead) & CRYPTO_TFM_NEED_KEY)
		goto unlock;

	if (!pask->refcnt++)
		sock_hold(psk);

	ask->refcnt = 1;
	sock_put(psk);

	err = 0;

unlock:
	release_sock(psk);
unlock_child:
	release_sock(sk);

	return err;
}