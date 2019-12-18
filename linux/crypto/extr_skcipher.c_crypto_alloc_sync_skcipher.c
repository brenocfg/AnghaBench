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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_sync_skcipher {int dummy; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  EINVAL ; 
 struct crypto_sync_skcipher* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct crypto_skcipher*) ; 
 scalar_t__ MAX_SYNC_SKCIPHER_REQSIZE ; 
 scalar_t__ WARN_ON (int) ; 
 struct crypto_skcipher* crypto_alloc_tfm (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 scalar_t__ crypto_skcipher_reqsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_type2 ; 

struct crypto_sync_skcipher *crypto_alloc_sync_skcipher(
				const char *alg_name, u32 type, u32 mask)
{
	struct crypto_skcipher *tfm;

	/* Only sync algorithms allowed. */
	mask |= CRYPTO_ALG_ASYNC;

	tfm = crypto_alloc_tfm(alg_name, &crypto_skcipher_type2, type, mask);

	/*
	 * Make sure we do not allocate something that might get used with
	 * an on-stack request: check the request size.
	 */
	if (!IS_ERR(tfm) && WARN_ON(crypto_skcipher_reqsize(tfm) >
				    MAX_SYNC_SKCIPHER_REQSIZE)) {
		crypto_free_skcipher(tfm);
		return ERR_PTR(-EINVAL);
	}

	return (struct crypto_sync_skcipher *)tfm;
}