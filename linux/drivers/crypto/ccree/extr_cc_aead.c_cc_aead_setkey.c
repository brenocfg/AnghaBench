#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct crypto_authenc_keys {int enckeylen; int authkeylen; int /*<<< orphan*/ * authkey; int /*<<< orphan*/ * enckey; } ;
struct crypto_aead {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_crypto_req {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  xcbc_keys; } ;
struct TYPE_4__ {TYPE_1__ xcbc; } ;
struct cc_aead_ctx {int auth_mode; int enc_keylen; int auth_keylen; scalar_t__ cipher_mode; int /*<<< orphan*/  drvdata; TYPE_2__ auth_state; int /*<<< orphan*/  enckey; int /*<<< orphan*/  ctr_nonce; } ;

/* Variables and functions */
 int AES_MIN_KEY_SIZE ; 
 scalar_t__ CC_AES_KEY_SIZE_MAX ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CTR_RFC3686_NONCE_SIZE ; 
 scalar_t__ DRV_CIPHER_CTR ; 
#define  DRV_HASH_NULL 131 
#define  DRV_HASH_SHA1 130 
#define  DRV_HASH_SHA256 129 
#define  DRV_HASH_XCBC_MAC 128 
 int EINVAL ; 
 int ENOTSUPP ; 
 int MAX_AEAD_SETKEY_SEQ ; 
 int cc_get_plain_hmac_key (struct crypto_aead*,int /*<<< orphan*/  const*,int) ; 
 int cc_send_sync_request (int /*<<< orphan*/ ,struct cc_crypto_req*,struct cc_hw_desc*,unsigned int) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_tfm (struct crypto_aead*) ; 
 int crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_tfm_alg_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct cc_aead_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 unsigned int hmac_setkey (struct cc_hw_desc*,struct cc_aead_ctx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int validate_keys_sizes (struct cc_aead_ctx*) ; 
 unsigned int xcbc_setkey (struct cc_hw_desc*,struct cc_aead_ctx*) ; 

__attribute__((used)) static int cc_aead_setkey(struct crypto_aead *tfm, const u8 *key,
			  unsigned int keylen)
{
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct cc_crypto_req cc_req = {};
	struct cc_hw_desc desc[MAX_AEAD_SETKEY_SEQ];
	unsigned int seq_len = 0;
	struct device *dev = drvdata_to_dev(ctx->drvdata);
	const u8 *enckey, *authkey;
	int rc;

	dev_dbg(dev, "Setting key in context @%p for %s. key=%p keylen=%u\n",
		ctx, crypto_tfm_alg_name(crypto_aead_tfm(tfm)), key, keylen);

	/* STAT_PHASE_0: Init and sanity checks */

	if (ctx->auth_mode != DRV_HASH_NULL) { /* authenc() alg. */
		struct crypto_authenc_keys keys;

		rc = crypto_authenc_extractkeys(&keys, key, keylen);
		if (rc)
			goto badkey;
		enckey = keys.enckey;
		authkey = keys.authkey;
		ctx->enc_keylen = keys.enckeylen;
		ctx->auth_keylen = keys.authkeylen;

		if (ctx->cipher_mode == DRV_CIPHER_CTR) {
			/* the nonce is stored in bytes at end of key */
			rc = -EINVAL;
			if (ctx->enc_keylen <
			    (AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE))
				goto badkey;
			/* Copy nonce from last 4 bytes in CTR key to
			 *  first 4 bytes in CTR IV
			 */
			memcpy(ctx->ctr_nonce, enckey + ctx->enc_keylen -
			       CTR_RFC3686_NONCE_SIZE, CTR_RFC3686_NONCE_SIZE);
			/* Set CTR key size */
			ctx->enc_keylen -= CTR_RFC3686_NONCE_SIZE;
		}
	} else { /* non-authenc - has just one key */
		enckey = key;
		authkey = NULL;
		ctx->enc_keylen = keylen;
		ctx->auth_keylen = 0;
	}

	rc = validate_keys_sizes(ctx);
	if (rc)
		goto badkey;

	/* STAT_PHASE_1: Copy key to ctx */

	/* Get key material */
	memcpy(ctx->enckey, enckey, ctx->enc_keylen);
	if (ctx->enc_keylen == 24)
		memset(ctx->enckey + 24, 0, CC_AES_KEY_SIZE_MAX - 24);
	if (ctx->auth_mode == DRV_HASH_XCBC_MAC) {
		memcpy(ctx->auth_state.xcbc.xcbc_keys, authkey,
		       ctx->auth_keylen);
	} else if (ctx->auth_mode != DRV_HASH_NULL) { /* HMAC */
		rc = cc_get_plain_hmac_key(tfm, authkey, ctx->auth_keylen);
		if (rc)
			goto badkey;
	}

	/* STAT_PHASE_2: Create sequence */

	switch (ctx->auth_mode) {
	case DRV_HASH_SHA1:
	case DRV_HASH_SHA256:
		seq_len = hmac_setkey(desc, ctx);
		break;
	case DRV_HASH_XCBC_MAC:
		seq_len = xcbc_setkey(desc, ctx);
		break;
	case DRV_HASH_NULL: /* non-authenc modes, e.g., CCM */
		break; /* No auth. key setup */
	default:
		dev_err(dev, "Unsupported authenc (%d)\n", ctx->auth_mode);
		rc = -ENOTSUPP;
		goto badkey;
	}

	/* STAT_PHASE_3: Submit sequence to HW */

	if (seq_len > 0) { /* For CCM there is no sequence to setup the key */
		rc = cc_send_sync_request(ctx->drvdata, &cc_req, desc, seq_len);
		if (rc) {
			dev_err(dev, "send_request() failed (rc=%d)\n", rc);
			goto setkey_error;
		}
	}

	/* Update STAT_PHASE_3 */
	return rc;

badkey:
	crypto_aead_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);

setkey_error:
	return rc;
}