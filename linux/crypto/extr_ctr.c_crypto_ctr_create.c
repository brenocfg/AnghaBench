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
struct TYPE_3__ {int cra_blocksize; } ;
struct TYPE_4__ {int chunksize; void* decrypt; void* encrypt; TYPE_1__ base; } ;
struct skcipher_instance {int /*<<< orphan*/  (* free ) (struct skcipher_instance*) ;TYPE_2__ alg; } ;
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_alg {int cra_blocksize; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct skcipher_instance*) ; 
 int PTR_ERR (struct skcipher_instance*) ; 
 void* crypto_ctr_crypt ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 struct skcipher_instance* skcipher_alloc_instance_simple (struct crypto_template*,struct rtattr**,struct crypto_alg**) ; 
 int skcipher_register_instance (struct crypto_template*,struct skcipher_instance*) ; 
 int /*<<< orphan*/  stub1 (struct skcipher_instance*) ; 

__attribute__((used)) static int crypto_ctr_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct skcipher_instance *inst;
	struct crypto_alg *alg;
	int err;

	inst = skcipher_alloc_instance_simple(tmpl, tb, &alg);
	if (IS_ERR(inst))
		return PTR_ERR(inst);

	/* Block size must be >= 4 bytes. */
	err = -EINVAL;
	if (alg->cra_blocksize < 4)
		goto out_free_inst;

	/* If this is false we'd fail the alignment of crypto_inc. */
	if (alg->cra_blocksize % 4)
		goto out_free_inst;

	/* CTR mode is a stream cipher. */
	inst->alg.base.cra_blocksize = 1;

	/*
	 * To simplify the implementation, configure the skcipher walk to only
	 * give a partial block at the very end, never earlier.
	 */
	inst->alg.chunksize = alg->cra_blocksize;

	inst->alg.encrypt = crypto_ctr_crypt;
	inst->alg.decrypt = crypto_ctr_crypt;

	err = skcipher_register_instance(tmpl, inst);
	if (err)
		goto out_free_inst;
	goto out_put_alg;

out_free_inst:
	inst->free(inst);
out_put_alg:
	crypto_mod_put(alg);
	return err;
}