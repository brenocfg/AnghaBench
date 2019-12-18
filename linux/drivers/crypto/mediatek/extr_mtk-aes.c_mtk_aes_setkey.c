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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_aes_base_ctx {int /*<<< orphan*/  key; int /*<<< orphan*/  keylen; int /*<<< orphan*/  keymode; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int /*<<< orphan*/  AES_TFM_128BITS ; 
 int /*<<< orphan*/  AES_TFM_192BITS ; 
 int /*<<< orphan*/  AES_TFM_256BITS ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  SIZE_IN_WORDS (int /*<<< orphan*/ ) ; 
 struct mtk_aes_base_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_aes_write_state_le (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_aes_setkey(struct crypto_ablkcipher *tfm,
			  const u8 *key, u32 keylen)
{
	struct mtk_aes_base_ctx *ctx = crypto_ablkcipher_ctx(tfm);

	switch (keylen) {
	case AES_KEYSIZE_128:
		ctx->keymode = AES_TFM_128BITS;
		break;
	case AES_KEYSIZE_192:
		ctx->keymode = AES_TFM_192BITS;
		break;
	case AES_KEYSIZE_256:
		ctx->keymode = AES_TFM_256BITS;
		break;

	default:
		crypto_ablkcipher_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	ctx->keylen = SIZE_IN_WORDS(keylen);
	mtk_aes_write_state_le(ctx->key, (const u32 *)key, keylen);

	return 0;
}