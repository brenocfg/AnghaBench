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
struct xts_instance_ctx {int /*<<< orphan*/  name; int /*<<< orphan*/  spawn; } ;
struct skcipher_instance {int dummy; } ;
struct rctx {int dummy; } ;
struct priv {struct crypto_skcipher* tweak; struct crypto_skcipher* child; } ;
struct crypto_skcipher {int dummy; } ;
typedef  struct crypto_skcipher crypto_cipher ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_alloc_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 struct priv* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 scalar_t__ crypto_skcipher_reqsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_reqsize (struct crypto_skcipher*,scalar_t__) ; 
 struct crypto_skcipher* crypto_spawn_skcipher (int /*<<< orphan*/ *) ; 
 struct skcipher_instance* skcipher_alg_instance (struct crypto_skcipher*) ; 
 struct xts_instance_ctx* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static int init_tfm(struct crypto_skcipher *tfm)
{
	struct skcipher_instance *inst = skcipher_alg_instance(tfm);
	struct xts_instance_ctx *ictx = skcipher_instance_ctx(inst);
	struct priv *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *child;
	struct crypto_cipher *tweak;

	child = crypto_spawn_skcipher(&ictx->spawn);
	if (IS_ERR(child))
		return PTR_ERR(child);

	ctx->child = child;

	tweak = crypto_alloc_cipher(ictx->name, 0, 0);
	if (IS_ERR(tweak)) {
		crypto_free_skcipher(ctx->child);
		return PTR_ERR(tweak);
	}

	ctx->tweak = tweak;

	crypto_skcipher_set_reqsize(tfm, crypto_skcipher_reqsize(child) +
					 sizeof(struct rctx));

	return 0;
}