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
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_crypto_priv {int flags; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int needs_inv; scalar_t__ ctxr_dma; } ;
struct safexcel_cipher_ctx {scalar_t__ mode; int alg; int hash_alg; scalar_t__ state_sz; scalar_t__ key_len; int /*<<< orphan*/  opad; int /*<<< orphan*/  ipad; int /*<<< orphan*/  key; TYPE_1__ base; int /*<<< orphan*/  nonce; struct safexcel_crypto_priv* priv; } ;
struct safexcel_ahash_export_state {scalar_t__ state; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_authenc_keys {scalar_t__ enckeylen; scalar_t__ enckey; int /*<<< orphan*/  authkeylen; int /*<<< orphan*/  authkey; } ;
struct crypto_aes_ctx {int dummy; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
 scalar_t__ AES_MIN_KEY_SIZE ; 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA1 134 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA224 133 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA256 132 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA384 131 
#define  CONTEXT_CONTROL_CRYPTO_ALG_SHA512 130 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD ; 
 int CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 scalar_t__ CTR_RFC3686_NONCE_SIZE ; 
 int EINVAL ; 
 int EIP197_TRC_CACHE ; 
#define  SAFEXCEL_3DES 129 
#define  SAFEXCEL_AES 128 
 int aes_expandkey (struct crypto_aes_ctx*,scalar_t__,scalar_t__) ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int) ; 
 struct crypto_tfm* crypto_aead_tfm (struct crypto_aead*) ; 
 scalar_t__ crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_authenc_keys*,int) ; 
 int /*<<< orphan*/  safexcel_hmac_setkey (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_ahash_export_state*,struct safexcel_ahash_export_state*) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int verify_aead_des3_key (struct crypto_aead*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int safexcel_aead_setkey(struct crypto_aead *ctfm, const u8 *key,
				unsigned int len)
{
	struct crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_ahash_export_state istate, ostate;
	struct safexcel_crypto_priv *priv = ctx->priv;
	struct crypto_authenc_keys keys;
	struct crypto_aes_ctx aes;
	int err = -EINVAL;

	if (crypto_authenc_extractkeys(&keys, key, len) != 0)
		goto badkey;

	if (ctx->mode == CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD) {
		/* Minimum keysize is minimum AES key size + nonce size */
		if (keys.enckeylen < (AES_MIN_KEY_SIZE +
				      CTR_RFC3686_NONCE_SIZE))
			goto badkey;
		/* last 4 bytes of key are the nonce! */
		ctx->nonce = *(u32 *)(keys.enckey + keys.enckeylen -
				      CTR_RFC3686_NONCE_SIZE);
		/* exclude the nonce here */
		keys.enckeylen -= CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD;
	}

	/* Encryption key */
	switch (ctx->alg) {
	case SAFEXCEL_3DES:
		err = verify_aead_des3_key(ctfm, keys.enckey, keys.enckeylen);
		if (unlikely(err))
			goto badkey_expflags;
		break;
	case SAFEXCEL_AES:
		err = aes_expandkey(&aes, keys.enckey, keys.enckeylen);
		if (unlikely(err))
			goto badkey;
		break;
	default:
		dev_err(priv->dev, "aead: unsupported cipher algorithm\n");
		goto badkey;
	}

	if (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma &&
	    memcmp(ctx->key, keys.enckey, keys.enckeylen))
		ctx->base.needs_inv = true;

	/* Auth key */
	switch (ctx->hash_alg) {
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA1:
		if (safexcel_hmac_setkey("safexcel-sha1", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA224:
		if (safexcel_hmac_setkey("safexcel-sha224", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA256:
		if (safexcel_hmac_setkey("safexcel-sha256", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA384:
		if (safexcel_hmac_setkey("safexcel-sha384", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	case CONTEXT_CONTROL_CRYPTO_ALG_SHA512:
		if (safexcel_hmac_setkey("safexcel-sha512", keys.authkey,
					 keys.authkeylen, &istate, &ostate))
			goto badkey;
		break;
	default:
		dev_err(priv->dev, "aead: unsupported hash algorithm\n");
		goto badkey;
	}

	crypto_aead_set_flags(ctfm, crypto_aead_get_flags(ctfm) &
				    CRYPTO_TFM_RES_MASK);

	if (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma &&
	    (memcmp(ctx->ipad, istate.state, ctx->state_sz) ||
	     memcmp(ctx->opad, ostate.state, ctx->state_sz)))
		ctx->base.needs_inv = true;

	/* Now copy the keys into the context */
	memcpy(ctx->key, keys.enckey, keys.enckeylen);
	ctx->key_len = keys.enckeylen;

	memcpy(ctx->ipad, &istate.state, ctx->state_sz);
	memcpy(ctx->opad, &ostate.state, ctx->state_sz);

	memzero_explicit(&keys, sizeof(keys));
	return 0;

badkey:
	crypto_aead_set_flags(ctfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
badkey_expflags:
	memzero_explicit(&keys, sizeof(keys));
	return err;
}