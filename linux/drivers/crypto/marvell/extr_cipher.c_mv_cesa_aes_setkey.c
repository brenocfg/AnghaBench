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
struct TYPE_2__ {int key_length; int /*<<< orphan*/ * key_enc; int /*<<< orphan*/ * key_dec; } ;
struct mv_cesa_aes_ctx {TYPE_1__ aes; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int aes_expandkey (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_tfm* crypto_skcipher_tfm (struct crypto_skcipher*) ; 
 struct mv_cesa_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int mv_cesa_aes_setkey(struct crypto_skcipher *cipher, const u8 *key,
			      unsigned int len)
{
	struct crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	struct mv_cesa_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	int remaining;
	int offset;
	int ret;
	int i;

	ret = aes_expandkey(&ctx->aes, key, len);
	if (ret) {
		crypto_skcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return ret;
	}

	remaining = (ctx->aes.key_length - 16) / 4;
	offset = ctx->aes.key_length + 24 - remaining;
	for (i = 0; i < remaining; i++)
		ctx->aes.key_dec[4 + i] =
			cpu_to_le32(ctx->aes.key_enc[offset + i]);

	return 0;
}