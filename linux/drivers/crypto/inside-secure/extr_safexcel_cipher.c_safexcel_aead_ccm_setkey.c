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
struct safexcel_crypto_priv {int flags; } ;
struct TYPE_2__ {int needs_inv; scalar_t__ ctxr_dma; } ;
struct safexcel_cipher_ctx {scalar_t__* key; unsigned int key_len; int state_sz; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/ * ipad; TYPE_1__ base; struct safexcel_crypto_priv* priv; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_aes_ctx {int /*<<< orphan*/ * key_enc; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  aes ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 unsigned int AES_KEYSIZE_192 ; 
 unsigned int AES_KEYSIZE_256 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_XCBC128 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_XCBC192 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_XCBC256 ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EIP197_TRC_CACHE ; 
 int aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_aead_tfm (struct crypto_aead*) ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_aes_ctx*,int) ; 

__attribute__((used)) static int safexcel_aead_ccm_setkey(struct crypto_aead *ctfm, const u8 *key,
				    unsigned int len)
{
	struct crypto_tfm *tfm = crypto_aead_tfm(ctfm);
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_crypto_priv *priv = ctx->priv;
	struct crypto_aes_ctx aes;
	int ret, i;

	ret = aes_expandkey(&aes, key, len);
	if (ret) {
		crypto_aead_set_flags(ctfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		memzero_explicit(&aes, sizeof(aes));
		return ret;
	}

	if (priv->flags & EIP197_TRC_CACHE && ctx->base.ctxr_dma) {
		for (i = 0; i < len / sizeof(u32); i++) {
			if (ctx->key[i] != cpu_to_le32(aes.key_enc[i])) {
				ctx->base.needs_inv = true;
				break;
			}
		}
	}

	for (i = 0; i < len / sizeof(u32); i++) {
		ctx->key[i] = cpu_to_le32(aes.key_enc[i]);
		ctx->ipad[i + 2 * AES_BLOCK_SIZE / sizeof(u32)] =
			cpu_to_be32(aes.key_enc[i]);
	}

	ctx->key_len = len;
	ctx->state_sz = 2 * AES_BLOCK_SIZE + len;

	if (len == AES_KEYSIZE_192)
		ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_XCBC192;
	else if (len == AES_KEYSIZE_256)
		ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_XCBC256;
	else
		ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_XCBC128;

	memzero_explicit(&aes, sizeof(aes));
	return 0;
}