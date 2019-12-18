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
struct crypto_alg {int cra_alignmask; scalar_t__ cra_blocksize; int cra_flags; scalar_t__ cra_priority; int /*<<< orphan*/  cra_refcnt; int /*<<< orphan*/  cra_type; int /*<<< orphan*/ * cra_driver_name; int /*<<< orphan*/ * cra_name; int /*<<< orphan*/  cra_module; } ;

/* Variables and functions */
 int CRYPTO_ALG_TYPE_CIPHER ; 
 int CRYPTO_ALG_TYPE_MASK ; 
 int EINVAL ; 
 int MAX_ALGAPI_ALIGNMASK ; 
 scalar_t__ MAX_ALGAPI_BLOCKSIZE ; 
 int MAX_CIPHER_ALIGNMASK ; 
 scalar_t__ MAX_CIPHER_BLOCKSIZE ; 
 int /*<<< orphan*/  crypto_check_module_sig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int crypto_check_alg(struct crypto_alg *alg)
{
	crypto_check_module_sig(alg->cra_module);

	if (!alg->cra_name[0] || !alg->cra_driver_name[0])
		return -EINVAL;

	if (alg->cra_alignmask & (alg->cra_alignmask + 1))
		return -EINVAL;

	/* General maximums for all algs. */
	if (alg->cra_alignmask > MAX_ALGAPI_ALIGNMASK)
		return -EINVAL;

	if (alg->cra_blocksize > MAX_ALGAPI_BLOCKSIZE)
		return -EINVAL;

	/* Lower maximums for specific alg types. */
	if (!alg->cra_type && (alg->cra_flags & CRYPTO_ALG_TYPE_MASK) ==
			       CRYPTO_ALG_TYPE_CIPHER) {
		if (alg->cra_alignmask > MAX_CIPHER_ALIGNMASK)
			return -EINVAL;

		if (alg->cra_blocksize > MAX_CIPHER_BLOCKSIZE)
			return -EINVAL;
	}

	if (alg->cra_priority < 0)
		return -EINVAL;

	refcount_set(&alg->cra_refcnt, 1);

	return 0;
}