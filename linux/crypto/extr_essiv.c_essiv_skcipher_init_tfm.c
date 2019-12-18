#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skcipher_request {int dummy; } ;
struct skcipher_instance {int dummy; } ;
struct TYPE_3__ {struct crypto_skcipher* skcipher; } ;
struct essiv_tfm_ctx {TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  skcipher_spawn; } ;
struct essiv_instance_ctx {TYPE_2__ u; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 struct essiv_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 scalar_t__ crypto_skcipher_reqsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_reqsize (struct crypto_skcipher*,scalar_t__) ; 
 struct crypto_skcipher* crypto_spawn_skcipher (int /*<<< orphan*/ *) ; 
 int essiv_init_tfm (struct essiv_instance_ctx*,struct essiv_tfm_ctx*) ; 
 struct skcipher_instance* skcipher_alg_instance (struct crypto_skcipher*) ; 
 struct essiv_instance_ctx* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static int essiv_skcipher_init_tfm(struct crypto_skcipher *tfm)
{
	struct skcipher_instance *inst = skcipher_alg_instance(tfm);
	struct essiv_instance_ctx *ictx = skcipher_instance_ctx(inst);
	struct essiv_tfm_ctx *tctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *skcipher;
	int err;

	skcipher = crypto_spawn_skcipher(&ictx->u.skcipher_spawn);
	if (IS_ERR(skcipher))
		return PTR_ERR(skcipher);

	crypto_skcipher_set_reqsize(tfm, sizeof(struct skcipher_request) +
				         crypto_skcipher_reqsize(skcipher));

	err = essiv_init_tfm(ictx, tctx);
	if (err) {
		crypto_free_skcipher(skcipher);
		return err;
	}

	tctx->u.skcipher = skcipher;
	return 0;
}