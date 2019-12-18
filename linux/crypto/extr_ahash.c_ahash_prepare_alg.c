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
struct crypto_alg {int /*<<< orphan*/  cra_flags; int /*<<< orphan*/ * cra_type; } ;
struct TYPE_2__ {scalar_t__ digestsize; scalar_t__ statesize; struct crypto_alg base; } ;
struct ahash_alg {TYPE_1__ halg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_AHASH ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int EINVAL ; 
 scalar_t__ HASH_MAX_DIGESTSIZE ; 
 scalar_t__ HASH_MAX_STATESIZE ; 
 int /*<<< orphan*/  crypto_ahash_type ; 

__attribute__((used)) static int ahash_prepare_alg(struct ahash_alg *alg)
{
	struct crypto_alg *base = &alg->halg.base;

	if (alg->halg.digestsize > HASH_MAX_DIGESTSIZE ||
	    alg->halg.statesize > HASH_MAX_STATESIZE ||
	    alg->halg.statesize == 0)
		return -EINVAL;

	base->cra_type = &crypto_ahash_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_AHASH;

	return 0;
}