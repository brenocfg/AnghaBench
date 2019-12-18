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
struct TYPE_3__ {scalar_t__ cra_alignmask; void* cra_blocksize; } ;
struct TYPE_4__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; void* ivsize; TYPE_1__ base; } ;
struct skcipher_instance {int /*<<< orphan*/  (* free ) (struct skcipher_instance*) ;TYPE_2__ alg; } ;
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_kw_block {int dummy; } ;
struct crypto_alg {int cra_blocksize; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct skcipher_instance*) ; 
 int PTR_ERR (struct skcipher_instance*) ; 
 void* SEMIBSIZE ; 
 int /*<<< orphan*/  crypto_kw_decrypt ; 
 int /*<<< orphan*/  crypto_kw_encrypt ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 struct skcipher_instance* skcipher_alloc_instance_simple (struct crypto_template*,struct rtattr**,struct crypto_alg**) ; 
 int skcipher_register_instance (struct crypto_template*,struct skcipher_instance*) ; 
 int /*<<< orphan*/  stub1 (struct skcipher_instance*) ; 

__attribute__((used)) static int crypto_kw_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct skcipher_instance *inst;
	struct crypto_alg *alg;
	int err;

	inst = skcipher_alloc_instance_simple(tmpl, tb, &alg);
	if (IS_ERR(inst))
		return PTR_ERR(inst);

	err = -EINVAL;
	/* Section 5.1 requirement for KW */
	if (alg->cra_blocksize != sizeof(struct crypto_kw_block))
		goto out_free_inst;

	inst->alg.base.cra_blocksize = SEMIBSIZE;
	inst->alg.base.cra_alignmask = 0;
	inst->alg.ivsize = SEMIBSIZE;

	inst->alg.encrypt = crypto_kw_encrypt;
	inst->alg.decrypt = crypto_kw_decrypt;

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