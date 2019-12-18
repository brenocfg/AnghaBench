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
struct crypto_alg {int cra_blocksize; int /*<<< orphan*/  cra_flags; int /*<<< orphan*/ * cra_type; } ;
struct skcipher_alg {int ivsize; int chunksize; int walksize; struct crypto_alg base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_SKCIPHER ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  crypto_skcipher_type2 ; 

__attribute__((used)) static int skcipher_prepare_alg(struct skcipher_alg *alg)
{
	struct crypto_alg *base = &alg->base;

	if (alg->ivsize > PAGE_SIZE / 8 || alg->chunksize > PAGE_SIZE / 8 ||
	    alg->walksize > PAGE_SIZE / 8)
		return -EINVAL;

	if (!alg->chunksize)
		alg->chunksize = base->cra_blocksize;
	if (!alg->walksize)
		alg->walksize = alg->chunksize;

	base->cra_type = &crypto_skcipher_type2;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_SKCIPHER;

	return 0;
}