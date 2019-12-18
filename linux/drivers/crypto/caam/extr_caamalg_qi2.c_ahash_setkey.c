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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_ahash {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {unsigned int keylen; unsigned int keylen_pad; int algtype; int key_inline; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  const* key_virt; } ;
struct caam_hash_ctx {TYPE_1__ adata; int /*<<< orphan*/  dev; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 unsigned int CAAM_MAX_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int OP_ALG_ALGSEL_MASK ; 
 int ahash_set_sh_desc (struct crypto_ahash*) ; 
 struct caam_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 unsigned int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int hash_digest_key (struct caam_hash_ctx*,unsigned int*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int split_key_len (int) ; 

__attribute__((used)) static int ahash_setkey(struct crypto_ahash *ahash, const u8 *key,
			unsigned int keylen)
{
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	unsigned int blocksize = crypto_tfm_alg_blocksize(&ahash->base);
	unsigned int digestsize = crypto_ahash_digestsize(ahash);
	int ret;
	u8 *hashed_key = NULL;

	dev_dbg(ctx->dev, "keylen %d blocksize %d\n", keylen, blocksize);

	if (keylen > blocksize) {
		hashed_key = kmemdup(key, keylen, GFP_KERNEL | GFP_DMA);
		if (!hashed_key)
			return -ENOMEM;
		ret = hash_digest_key(ctx, &keylen, hashed_key, digestsize);
		if (ret)
			goto bad_free_key;
		key = hashed_key;
	}

	ctx->adata.keylen = keylen;
	ctx->adata.keylen_pad = split_key_len(ctx->adata.algtype &
					      OP_ALG_ALGSEL_MASK);
	if (ctx->adata.keylen_pad > CAAM_MAX_HASH_KEY_SIZE)
		goto bad_free_key;

	ctx->adata.key_virt = key;
	ctx->adata.key_inline = true;

	/*
	 * In case |user key| > |derived key|, using DKP<imm,imm> would result
	 * in invalid opcodes (last bytes of user key) in the resulting
	 * descriptor. Use DKP<ptr,imm> instead => both virtual and dma key
	 * addresses are needed.
	 */
	if (keylen > ctx->adata.keylen_pad) {
		memcpy(ctx->key, key, keylen);
		dma_sync_single_for_device(ctx->dev, ctx->adata.key_dma,
					   ctx->adata.keylen_pad,
					   DMA_TO_DEVICE);
	}

	ret = ahash_set_sh_desc(ahash);
	kfree(hashed_key);
	return ret;
bad_free_key:
	kfree(hashed_key);
	crypto_ahash_set_flags(ahash, CRYPTO_TFM_RES_BAD_KEY_LEN);
	return -EINVAL;
}