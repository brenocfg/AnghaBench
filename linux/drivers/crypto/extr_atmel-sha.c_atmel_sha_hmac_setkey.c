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
struct crypto_ahash {int dummy; } ;
struct atmel_sha_hmac_ctx {int /*<<< orphan*/  hkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 scalar_t__ atmel_sha_hmac_key_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct atmel_sha_hmac_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_sha_hmac_setkey(struct crypto_ahash *tfm, const u8 *key,
				 unsigned int keylen)
{
	struct atmel_sha_hmac_ctx *hmac = crypto_ahash_ctx(tfm);

	if (atmel_sha_hmac_key_set(&hmac->hkey, key, keylen)) {
		crypto_ahash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	return 0;
}