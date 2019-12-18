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
struct TYPE_2__ {int cra_flags; } ;
struct hash_alg_common {TYPE_1__ base; } ;
struct crypto_ahash {scalar_t__ setkey; } ;

/* Variables and functions */
 int CRYPTO_ALG_OPTIONAL_KEY ; 
 int /*<<< orphan*/  CRYPTO_TFM_NEED_KEY ; 
 scalar_t__ ahash_nosetkey ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 struct hash_alg_common* crypto_hash_alg_common (struct crypto_ahash*) ; 

__attribute__((used)) static void ahash_set_needkey(struct crypto_ahash *tfm)
{
	const struct hash_alg_common *alg = crypto_hash_alg_common(tfm);

	if (tfm->setkey != ahash_nosetkey &&
	    !(alg->base.cra_flags & CRYPTO_ALG_OPTIONAL_KEY))
		crypto_ahash_set_flags(tfm, CRYPTO_TFM_NEED_KEY);
}