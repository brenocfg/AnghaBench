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
struct skcipher_instance {int dummy; } ;
struct crypto_skcipher_spawn {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_cts_reqctx {int dummy; } ;
struct crypto_cts_ctx {struct crypto_skcipher* child; } ;

/* Variables and functions */
 unsigned int ALIGN (scalar_t__,int) ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 unsigned int crypto_skcipher_alignmask (struct crypto_skcipher*) ; 
 unsigned int crypto_skcipher_blocksize (struct crypto_skcipher*) ; 
 struct crypto_cts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 scalar_t__ crypto_skcipher_reqsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_reqsize (struct crypto_skcipher*,unsigned int) ; 
 struct crypto_skcipher* crypto_spawn_skcipher (struct crypto_skcipher_spawn*) ; 
 int crypto_tfm_ctx_alignment () ; 
 struct skcipher_instance* skcipher_alg_instance (struct crypto_skcipher*) ; 
 struct crypto_skcipher_spawn* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static int crypto_cts_init_tfm(struct crypto_skcipher *tfm)
{
	struct skcipher_instance *inst = skcipher_alg_instance(tfm);
	struct crypto_skcipher_spawn *spawn = skcipher_instance_ctx(inst);
	struct crypto_cts_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *cipher;
	unsigned reqsize;
	unsigned bsize;
	unsigned align;

	cipher = crypto_spawn_skcipher(spawn);
	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctx->child = cipher;

	align = crypto_skcipher_alignmask(tfm);
	bsize = crypto_skcipher_blocksize(cipher);
	reqsize = ALIGN(sizeof(struct crypto_cts_reqctx) +
			crypto_skcipher_reqsize(cipher),
			crypto_tfm_ctx_alignment()) +
		  (align & ~(crypto_tfm_ctx_alignment() - 1)) + bsize;

	crypto_skcipher_set_reqsize(tfm, reqsize);

	return 0;
}