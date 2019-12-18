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
struct crypto_aead {int dummy; } ;
struct alg_sock {struct af_alg_ctx* private; struct sock* parent; } ;
struct af_alg_ctx {int /*<<< orphan*/  len; int /*<<< orphan*/  iv; int /*<<< orphan*/  used; struct crypto_aead* aead; } ;
struct aead_tfm {int /*<<< orphan*/  len; int /*<<< orphan*/  iv; int /*<<< orphan*/  used; struct crypto_aead* aead; } ;

/* Variables and functions */
 int /*<<< orphan*/  af_alg_pull_tsgl (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_alg_release_parent (struct sock*) ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct af_alg_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_kzfree_s (struct sock*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void aead_sock_destruct(struct sock *sk)
{
	struct alg_sock *ask = alg_sk(sk);
	struct af_alg_ctx *ctx = ask->private;
	struct sock *psk = ask->parent;
	struct alg_sock *pask = alg_sk(psk);
	struct aead_tfm *aeadc = pask->private;
	struct crypto_aead *tfm = aeadc->aead;
	unsigned int ivlen = crypto_aead_ivsize(tfm);

	af_alg_pull_tsgl(sk, ctx->used, NULL, 0);
	sock_kzfree_s(sk, ctx->iv, ivlen);
	sock_kfree_s(sk, ctx, ctx->len);
	af_alg_release_parent(sk);
}