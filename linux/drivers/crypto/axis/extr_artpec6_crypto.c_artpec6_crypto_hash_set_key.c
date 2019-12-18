#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypto_ahash {int /*<<< orphan*/  base; } ;
struct artpec6_hashalg_context {size_t hmac_key_length; int /*<<< orphan*/  hmac_key; int /*<<< orphan*/  child_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 int crypto_shash_digest (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 size_t crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 struct artpec6_hashalg_context* crypto_tfm_ctx (int /*<<< orphan*/ *) ; 
 TYPE_1__* hdesc ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static int
artpec6_crypto_hash_set_key(struct crypto_ahash *tfm,
		    const u8 *key, unsigned int keylen)
{
	struct artpec6_hashalg_context *tfm_ctx = crypto_tfm_ctx(&tfm->base);
	size_t blocksize;
	int ret;

	if (!keylen) {
		pr_err("Invalid length (%d) of HMAC key\n",
			keylen);
		return -EINVAL;
	}

	memset(tfm_ctx->hmac_key, 0, sizeof(tfm_ctx->hmac_key));

	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	if (keylen > blocksize) {
		SHASH_DESC_ON_STACK(hdesc, tfm_ctx->child_hash);

		hdesc->tfm = tfm_ctx->child_hash;

		tfm_ctx->hmac_key_length = blocksize;
		ret = crypto_shash_digest(hdesc, key, keylen,
					  tfm_ctx->hmac_key);
		if (ret)
			return ret;

	} else {
		memcpy(tfm_ctx->hmac_key, key, keylen);
		tfm_ctx->hmac_key_length = keylen;
	}

	return 0;
}