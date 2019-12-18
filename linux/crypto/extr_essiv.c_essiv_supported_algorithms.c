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
struct shash_alg {scalar_t__ digestsize; } ;
struct TYPE_2__ {scalar_t__ cia_min_keysize; scalar_t__ cia_max_keysize; } ;
struct crypto_alg {int cra_blocksize; TYPE_1__ cra_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_CIPHER ; 
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 scalar_t__ IS_ERR (struct crypto_alg*) ; 
 struct crypto_alg* crypto_alg_mod_lookup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 scalar_t__ crypto_shash_alg_has_setkey (struct shash_alg*) ; 

__attribute__((used)) static bool essiv_supported_algorithms(const char *essiv_cipher_name,
				       struct shash_alg *hash_alg,
				       int ivsize)
{
	struct crypto_alg *alg;
	bool ret = false;

	alg = crypto_alg_mod_lookup(essiv_cipher_name,
				    CRYPTO_ALG_TYPE_CIPHER,
				    CRYPTO_ALG_TYPE_MASK);
	if (IS_ERR(alg))
		return false;

	if (hash_alg->digestsize < alg->cra_cipher.cia_min_keysize ||
	    hash_alg->digestsize > alg->cra_cipher.cia_max_keysize)
		goto out;

	if (ivsize != alg->cra_blocksize)
		goto out;

	if (crypto_shash_alg_has_setkey(hash_alg))
		goto out;

	ret = true;

out:
	crypto_mod_put(alg);
	return ret;
}