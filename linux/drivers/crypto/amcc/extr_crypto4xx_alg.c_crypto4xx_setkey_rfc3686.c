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
struct crypto_skcipher {int dummy; } ;
struct crypto4xx_ctx {int /*<<< orphan*/  iv_nonce; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_FEEDBACK_MODE_NO_FB ; 
 int /*<<< orphan*/  CRYPTO_MODE_CTR ; 
 unsigned int CTR_RFC3686_NONCE_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32p (int /*<<< orphan*/ *) ; 
 int crypto4xx_setkey_aes (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto4xx_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

int crypto4xx_setkey_rfc3686(struct crypto_skcipher *cipher,
			     const u8 *key, unsigned int keylen)
{
	struct crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	int rc;

	rc = crypto4xx_setkey_aes(cipher, key, keylen - CTR_RFC3686_NONCE_SIZE,
		CRYPTO_MODE_CTR, CRYPTO_FEEDBACK_MODE_NO_FB);
	if (rc)
		return rc;

	ctx->iv_nonce = cpu_to_le32p((u32 *)&key[keylen -
						 CTR_RFC3686_NONCE_SIZE]);

	return 0;
}