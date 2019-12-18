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
struct crypto_skcipher {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cipher; } ;
struct crypto4xx_ctx {TYPE_1__ sw_cipher; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_skcipher_clear_flags (struct crypto_skcipher*,int) ; 
 int crypto_skcipher_get_flags (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_clear_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_sync_skcipher_set_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_sync_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int crypto4xx_sk_setup_fallback(struct crypto4xx_ctx *ctx,
				       struct crypto_skcipher *cipher,
				       const u8 *key,
				       unsigned int keylen)
{
	int rc;

	crypto_sync_skcipher_clear_flags(ctx->sw_cipher.cipher,
				    CRYPTO_TFM_REQ_MASK);
	crypto_sync_skcipher_set_flags(ctx->sw_cipher.cipher,
		crypto_skcipher_get_flags(cipher) & CRYPTO_TFM_REQ_MASK);
	rc = crypto_sync_skcipher_setkey(ctx->sw_cipher.cipher, key, keylen);
	crypto_skcipher_clear_flags(cipher, CRYPTO_TFM_RES_MASK);
	crypto_skcipher_set_flags(cipher,
		crypto_sync_skcipher_get_flags(ctx->sw_cipher.cipher) &
			CRYPTO_TFM_RES_MASK);

	return rc;
}