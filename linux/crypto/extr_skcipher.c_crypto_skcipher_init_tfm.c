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
struct skcipher_alg {int (* init ) (struct crypto_skcipher*) ;scalar_t__ exit; int /*<<< orphan*/  max_keysize; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit; } ;
struct crypto_skcipher {TYPE_2__ base; int /*<<< orphan*/  keysize; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cra_type; } ;

/* Variables and functions */
 struct crypto_skcipher* __crypto_skcipher_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_type ; 
 int /*<<< orphan*/  crypto_blkcipher_type ; 
 int crypto_init_skcipher_ops_ablkcipher (struct crypto_tfm*) ; 
 int crypto_init_skcipher_ops_blkcipher (struct crypto_tfm*) ; 
 struct skcipher_alg* crypto_skcipher_alg (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_exit_tfm ; 
 int /*<<< orphan*/  skcipher_set_needkey (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  skcipher_setkey ; 
 int stub1 (struct crypto_skcipher*) ; 

__attribute__((used)) static int crypto_skcipher_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_skcipher *skcipher = __crypto_skcipher_cast(tfm);
	struct skcipher_alg *alg = crypto_skcipher_alg(skcipher);

	if (tfm->__crt_alg->cra_type == &crypto_blkcipher_type)
		return crypto_init_skcipher_ops_blkcipher(tfm);

	if (tfm->__crt_alg->cra_type == &crypto_ablkcipher_type)
		return crypto_init_skcipher_ops_ablkcipher(tfm);

	skcipher->setkey = skcipher_setkey;
	skcipher->encrypt = alg->encrypt;
	skcipher->decrypt = alg->decrypt;
	skcipher->ivsize = alg->ivsize;
	skcipher->keysize = alg->max_keysize;

	skcipher_set_needkey(skcipher);

	if (alg->exit)
		skcipher->base.exit = crypto_skcipher_exit_tfm;

	if (alg->init)
		return alg->init(skcipher);

	return 0;
}