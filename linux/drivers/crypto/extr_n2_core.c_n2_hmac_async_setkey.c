#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {struct crypto_ahash* fallback_tfm; } ;
struct n2_hmac_ctx {unsigned int hash_key_len; int /*<<< orphan*/  hash_key; TYPE_1__ base; struct crypto_shash* child_shash; } ;
struct crypto_shash {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_6__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int N2_HASH_KEY_MAX ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_2__*,struct crypto_shash*) ; 
 struct n2_hmac_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_setkey (struct crypto_ahash*,int /*<<< orphan*/  const*,unsigned int) ; 
 int crypto_shash_blocksize (struct crypto_shash*) ; 
 int crypto_shash_digest (TYPE_2__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 int crypto_shash_digestsize (struct crypto_shash*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 TYPE_2__* shash ; 

__attribute__((used)) static int n2_hmac_async_setkey(struct crypto_ahash *tfm, const u8 *key,
				unsigned int keylen)
{
	struct n2_hmac_ctx *ctx = crypto_ahash_ctx(tfm);
	struct crypto_shash *child_shash = ctx->child_shash;
	struct crypto_ahash *fallback_tfm;
	SHASH_DESC_ON_STACK(shash, child_shash);
	int err, bs, ds;

	fallback_tfm = ctx->base.fallback_tfm;
	err = crypto_ahash_setkey(fallback_tfm, key, keylen);
	if (err)
		return err;

	shash->tfm = child_shash;

	bs = crypto_shash_blocksize(child_shash);
	ds = crypto_shash_digestsize(child_shash);
	BUG_ON(ds > N2_HASH_KEY_MAX);
	if (keylen > bs) {
		err = crypto_shash_digest(shash, key, keylen,
					  ctx->hash_key);
		if (err)
			return err;
		keylen = ds;
	} else if (keylen <= N2_HASH_KEY_MAX)
		memcpy(ctx->hash_key, key, keylen);

	ctx->hash_key_len = keylen;

	return err;
}