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
struct crypto_alg {int /*<<< orphan*/  cra_flags; int /*<<< orphan*/ * cra_type; int /*<<< orphan*/  cra_blocksize; } ;
struct aead_alg {int /*<<< orphan*/  chunksize; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  maxauthsize; struct crypto_alg base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_AEAD ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  crypto_aead_type ; 
 int max3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aead_prepare_alg(struct aead_alg *alg)
{
	struct crypto_alg *base = &alg->base;

	if (max3(alg->maxauthsize, alg->ivsize, alg->chunksize) >
	    PAGE_SIZE / 8)
		return -EINVAL;

	if (!alg->chunksize)
		alg->chunksize = base->cra_blocksize;

	base->cra_type = &crypto_aead_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_AEAD;

	return 0;
}