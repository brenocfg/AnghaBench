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
struct hash_ctx {int /*<<< orphan*/  len; } ;
struct alg_sock {struct hash_ctx* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  af_alg_release_parent (struct sock*) ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 int /*<<< orphan*/  hash_free_result (struct sock*,struct hash_ctx*) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct hash_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hash_sock_destruct(struct sock *sk)
{
	struct alg_sock *ask = alg_sk(sk);
	struct hash_ctx *ctx = ask->private;

	hash_free_result(sk, ctx);
	sock_kfree_s(sk, ctx, ctx->len);
	af_alg_release_parent(sk);
}