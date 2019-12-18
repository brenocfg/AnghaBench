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
typedef  int /*<<< orphan*/  u8 ;
struct talitos_ctx {size_t keylen; size_t enckeylen; size_t authkeylen; int /*<<< orphan*/ * key; int /*<<< orphan*/  dma_key; struct device* dev; } ;
struct device {int dummy; } ;
struct crypto_authenc_keys {size_t authkeylen; scalar_t__ enckeylen; int /*<<< orphan*/  enckey; int /*<<< orphan*/  authkey; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 scalar_t__ TALITOS_MAX_KEY_SIZE ; 
 struct talitos_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_authenc_keys*,int) ; 
 scalar_t__ unlikely (int) ; 
 int verify_aead_des3_key (struct crypto_aead*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int aead_des3_setkey(struct crypto_aead *authenc,
			    const u8 *key, unsigned int keylen)
{
	struct talitos_ctx *ctx = crypto_aead_ctx(authenc);
	struct device *dev = ctx->dev;
	struct crypto_authenc_keys keys;
	int err;

	err = crypto_authenc_extractkeys(&keys, key, keylen);
	if (unlikely(err))
		goto badkey;

	err = -EINVAL;
	if (keys.authkeylen + keys.enckeylen > TALITOS_MAX_KEY_SIZE)
		goto badkey;

	err = verify_aead_des3_key(authenc, keys.enckey, keys.enckeylen);
	if (err)
		goto out;

	if (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);

	memcpy(ctx->key, keys.authkey, keys.authkeylen);
	memcpy(&ctx->key[keys.authkeylen], keys.enckey, keys.enckeylen);

	ctx->keylen = keys.authkeylen + keys.enckeylen;
	ctx->enckeylen = keys.enckeylen;
	ctx->authkeylen = keys.authkeylen;
	ctx->dma_key = dma_map_single(dev, ctx->key, ctx->keylen,
				      DMA_TO_DEVICE);

out:
	memzero_explicit(&keys, sizeof(keys));
	return err;

badkey:
	crypto_aead_set_flags(authenc, CRYPTO_TFM_RES_BAD_KEY_LEN);
	goto out;
}