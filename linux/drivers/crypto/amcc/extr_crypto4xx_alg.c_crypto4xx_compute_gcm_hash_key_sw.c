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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct crypto_aes_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  ctx ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto4xx_memcpy_to_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_aes_ctx*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int crypto4xx_compute_gcm_hash_key_sw(__le32 *hash_start, const u8 *key,
					     unsigned int keylen)
{
	struct crypto_aes_ctx ctx;
	uint8_t src[16] = { 0 };
	int rc;

	rc = aes_expandkey(&ctx, key, keylen);
	if (rc) {
		pr_err("aes_expandkey() failed: %d\n", rc);
		return rc;
	}

	aes_encrypt(&ctx, src, src);
	crypto4xx_memcpy_to_le32(hash_start, src, 16);
	memzero_explicit(&ctx, sizeof(ctx));
	return 0;
}