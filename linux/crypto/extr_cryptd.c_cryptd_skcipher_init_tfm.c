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
struct crypto_skcipher_spawn {int dummy; } ;
struct skcipherd_instance_ctx {struct crypto_skcipher_spawn spawn; } ;
struct skcipher_instance {int dummy; } ;
struct crypto_sync_skcipher {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct cryptd_skcipher_request_ctx {int dummy; } ;
struct cryptd_skcipher_ctx {struct crypto_sync_skcipher* child; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 struct cryptd_skcipher_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_reqsize (struct crypto_skcipher*,int) ; 
 struct crypto_skcipher* crypto_spawn_skcipher (struct crypto_skcipher_spawn*) ; 
 struct skcipher_instance* skcipher_alg_instance (struct crypto_skcipher*) ; 
 struct skcipherd_instance_ctx* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static int cryptd_skcipher_init_tfm(struct crypto_skcipher *tfm)
{
	struct skcipher_instance *inst = skcipher_alg_instance(tfm);
	struct skcipherd_instance_ctx *ictx = skcipher_instance_ctx(inst);
	struct crypto_skcipher_spawn *spawn = &ictx->spawn;
	struct cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *cipher;

	cipher = crypto_spawn_skcipher(spawn);
	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctx->child = (struct crypto_sync_skcipher *)cipher;
	crypto_skcipher_set_reqsize(
		tfm, sizeof(struct cryptd_skcipher_request_ctx));
	return 0;
}