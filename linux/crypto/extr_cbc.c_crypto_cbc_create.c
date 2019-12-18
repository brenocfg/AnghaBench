#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct skcipher_instance {int /*<<< orphan*/  (* free ) (struct skcipher_instance*) ;TYPE_1__ alg; } ;
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_alg {int /*<<< orphan*/  cra_blocksize; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct skcipher_instance*) ; 
 int PTR_ERR (struct skcipher_instance*) ; 
 int /*<<< orphan*/  crypto_cbc_decrypt ; 
 int /*<<< orphan*/  crypto_cbc_encrypt ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int /*<<< orphan*/  is_power_of_2 (int /*<<< orphan*/ ) ; 
 struct skcipher_instance* skcipher_alloc_instance_simple (struct crypto_template*,struct rtattr**,struct crypto_alg**) ; 
 int skcipher_register_instance (struct crypto_template*,struct skcipher_instance*) ; 
 int /*<<< orphan*/  stub1 (struct skcipher_instance*) ; 

__attribute__((used)) static int crypto_cbc_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct skcipher_instance *inst;
	struct crypto_alg *alg;
	int err;

	inst = skcipher_alloc_instance_simple(tmpl, tb, &alg);
	if (IS_ERR(inst))
		return PTR_ERR(inst);

	err = -EINVAL;
	if (!is_power_of_2(alg->cra_blocksize))
		goto out_free_inst;

	inst->alg.encrypt = crypto_cbc_encrypt;
	inst->alg.decrypt = crypto_cbc_decrypt;

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