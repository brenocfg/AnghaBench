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
struct device {int /*<<< orphan*/  parent; } ;
struct crypto_ahash {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int key_inline; unsigned int keylen; unsigned int keylen_pad; int algtype; int /*<<< orphan*/  key_dma; } ;
struct caam_hash_ctx {TYPE_1__ adata; int /*<<< orphan*/  key; struct device* jrdev; } ;
struct caam_drv_private {int era; } ;

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
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int crypto_tfm_alg_blocksize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 struct caam_drv_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int gen_split_key (struct device*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*,unsigned int,unsigned int) ; 
 int hash_digest_key (struct caam_hash_ctx*,unsigned int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int split_key_len (int) ; 

__attribute__((used)) static int ahash_setkey(struct crypto_ahash *ahash,
			const u8 *key, unsigned int keylen)
{
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	struct device *jrdev = ctx->jrdev;
	int blocksize = crypto_tfm_alg_blocksize(&ahash->base);
	int digestsize = crypto_ahash_digestsize(ahash);
	struct caam_drv_private *ctrlpriv = dev_get_drvdata(ctx->jrdev->parent);
	int ret;
	u8 *hashed_key = NULL;

	dev_dbg(jrdev, "keylen %d\n", keylen);

	if (keylen > blocksize) {
		hashed_key = kmemdup(key, keylen, GFP_KERNEL | GFP_DMA);
		if (!hashed_key)
			return -ENOMEM;
		ret = hash_digest_key(ctx, &keylen, hashed_key, digestsize);
		if (ret)
			goto bad_free_key;
		key = hashed_key;
	}

	/*
	 * If DKP is supported, use it in the shared descriptor to generate
	 * the split key.
	 */
	if (ctrlpriv->era >= 6) {
		ctx->adata.key_inline = true;
		ctx->adata.keylen = keylen;
		ctx->adata.keylen_pad = split_key_len(ctx->adata.algtype &
						      OP_ALG_ALGSEL_MASK);

		if (ctx->adata.keylen_pad > CAAM_MAX_HASH_KEY_SIZE)
			goto bad_free_key;

		memcpy(ctx->key, key, keylen);

		/*
		 * In case |user key| > |derived key|, using DKP<imm,imm>
		 * would result in invalid opcodes (last bytes of user key) in
		 * the resulting descriptor. Use DKP<ptr,imm> instead => both
		 * virtual and dma key addresses are needed.
		 */
		if (keylen > ctx->adata.keylen_pad)
			dma_sync_single_for_device(ctx->jrdev,
						   ctx->adata.key_dma,
						   ctx->adata.keylen_pad,
						   DMA_TO_DEVICE);
	} else {
		ret = gen_split_key(ctx->jrdev, ctx->key, &ctx->adata, key,
				    keylen, CAAM_MAX_HASH_KEY_SIZE);
		if (ret)
			goto bad_free_key;
	}

	kfree(hashed_key);
	return ahash_set_sh_desc(ahash);
 bad_free_key:
	kfree(hashed_key);
	crypto_ahash_set_flags(ahash, CRYPTO_TFM_RES_BAD_KEY_LEN);
	return -EINVAL;
}