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
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 unsigned int CHACHA_KEY_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chacha20_skcipher_setkey(struct crypto_skcipher *skcipher,
				    const u8 *key, unsigned int keylen)
{
	if (keylen != CHACHA_KEY_SIZE) {
		crypto_skcipher_set_flags(skcipher,
					  CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	return skcipher_setkey(skcipher, key, keylen, 0);
}