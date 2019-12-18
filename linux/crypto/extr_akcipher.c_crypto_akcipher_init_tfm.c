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
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  exit; } ;
struct crypto_akcipher {TYPE_1__ base; } ;
struct akcipher_alg {int (* init ) (struct crypto_akcipher*) ;scalar_t__ exit; } ;

/* Variables and functions */
 struct crypto_akcipher* __crypto_akcipher_tfm (struct crypto_tfm*) ; 
 struct akcipher_alg* crypto_akcipher_alg (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  crypto_akcipher_exit_tfm ; 
 int stub1 (struct crypto_akcipher*) ; 

__attribute__((used)) static int crypto_akcipher_init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_akcipher *akcipher = __crypto_akcipher_tfm(tfm);
	struct akcipher_alg *alg = crypto_akcipher_alg(akcipher);

	if (alg->exit)
		akcipher->base.exit = crypto_akcipher_exit_tfm;

	if (alg->init)
		return alg->init(akcipher);

	return 0;
}