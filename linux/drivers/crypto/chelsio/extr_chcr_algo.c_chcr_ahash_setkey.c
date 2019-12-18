#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct hmac_ctx {int /*<<< orphan*/  const* opad; int /*<<< orphan*/  const* ipad; int /*<<< orphan*/  base_hash; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 struct hmac_ctx* HMAC_CTX (int /*<<< orphan*/ ) ; 
 unsigned int IPAD_DATA ; 
 unsigned int OPAD_DATA ; 
 unsigned int SHA224_DIGEST_SIZE ; 
 unsigned int SHA256_DIGEST_SIZE ; 
 unsigned int SHA384_DIGEST_SIZE ; 
 unsigned int SHA512_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chcr_change_order (int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int chcr_compute_partial_hash (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_shash_digest (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_ctx (struct crypto_ahash*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* shash ; 

__attribute__((used)) static int chcr_ahash_setkey(struct crypto_ahash *tfm, const u8 *key,
			     unsigned int keylen)
{
	struct hmac_ctx *hmacctx = HMAC_CTX(h_ctx(tfm));
	unsigned int digestsize = crypto_ahash_digestsize(tfm);
	unsigned int bs = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));
	unsigned int i, err = 0, updated_digestsize;

	SHASH_DESC_ON_STACK(shash, hmacctx->base_hash);

	/* use the key to calculate the ipad and opad. ipad will sent with the
	 * first request's data. opad will be sent with the final hash result
	 * ipad in hmacctx->ipad and opad in hmacctx->opad location
	 */
	shash->tfm = hmacctx->base_hash;
	if (keylen > bs) {
		err = crypto_shash_digest(shash, key, keylen,
					  hmacctx->ipad);
		if (err)
			goto out;
		keylen = digestsize;
	} else {
		memcpy(hmacctx->ipad, key, keylen);
	}
	memset(hmacctx->ipad + keylen, 0, bs - keylen);
	memcpy(hmacctx->opad, hmacctx->ipad, bs);

	for (i = 0; i < bs / sizeof(int); i++) {
		*((unsigned int *)(&hmacctx->ipad) + i) ^= IPAD_DATA;
		*((unsigned int *)(&hmacctx->opad) + i) ^= OPAD_DATA;
	}

	updated_digestsize = digestsize;
	if (digestsize == SHA224_DIGEST_SIZE)
		updated_digestsize = SHA256_DIGEST_SIZE;
	else if (digestsize == SHA384_DIGEST_SIZE)
		updated_digestsize = SHA512_DIGEST_SIZE;
	err = chcr_compute_partial_hash(shash, hmacctx->ipad,
					hmacctx->ipad, digestsize);
	if (err)
		goto out;
	chcr_change_order(hmacctx->ipad, updated_digestsize);

	err = chcr_compute_partial_hash(shash, hmacctx->opad,
					hmacctx->opad, digestsize);
	if (err)
		goto out;
	chcr_change_order(hmacctx->opad, updated_digestsize);
out:
	return err;
}