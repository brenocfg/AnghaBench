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
struct sock {int /*<<< orphan*/  sk_destruct; } ;
struct crypto_skcipher {int dummy; } ;
struct alg_sock {struct af_alg_ctx* private; } ;
struct af_alg_ctx {unsigned int len; int /*<<< orphan*/  wait; scalar_t__ enc; scalar_t__ merge; scalar_t__ more; int /*<<< orphan*/  rcvused; scalar_t__ used; int /*<<< orphan*/  tsgl_list; void* iv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_init_wait (int /*<<< orphan*/ *) ; 
 unsigned int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skcipher_sock_destruct ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct af_alg_ctx*,unsigned int) ; 
 void* sock_kmalloc (struct sock*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skcipher_accept_parent_nokey(void *private, struct sock *sk)
{
	struct af_alg_ctx *ctx;
	struct alg_sock *ask = alg_sk(sk);
	struct crypto_skcipher *tfm = private;
	unsigned int len = sizeof(*ctx);

	ctx = sock_kmalloc(sk, len, GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->iv = sock_kmalloc(sk, crypto_skcipher_ivsize(tfm),
			       GFP_KERNEL);
	if (!ctx->iv) {
		sock_kfree_s(sk, ctx, len);
		return -ENOMEM;
	}

	memset(ctx->iv, 0, crypto_skcipher_ivsize(tfm));

	INIT_LIST_HEAD(&ctx->tsgl_list);
	ctx->len = len;
	ctx->used = 0;
	atomic_set(&ctx->rcvused, 0);
	ctx->more = 0;
	ctx->merge = 0;
	ctx->enc = 0;
	crypto_init_wait(&ctx->wait);

	ask->private = ctx;

	sk->sk_destruct = skcipher_sock_destruct;

	return 0;
}