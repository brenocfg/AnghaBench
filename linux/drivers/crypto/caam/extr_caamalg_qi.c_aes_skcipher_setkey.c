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
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int aes_check_keylen (unsigned int) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aes_skcipher_setkey(struct crypto_skcipher *skcipher,
			       const u8 *key, unsigned int keylen)
{
	int err;

	err = aes_check_keylen(keylen);
	if (err) {
		crypto_skcipher_set_flags(skcipher,
					  CRYPTO_TFM_RES_BAD_KEY_LEN);
		return err;
	}

	return skcipher_setkey(skcipher, key, keylen, 0);
}