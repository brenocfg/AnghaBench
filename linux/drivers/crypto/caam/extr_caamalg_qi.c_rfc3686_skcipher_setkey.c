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
typedef  scalar_t__ u32 ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 scalar_t__ CTR_RFC3686_NONCE_SIZE ; 
 int aes_check_keylen (unsigned int) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int,scalar_t__) ; 

__attribute__((used)) static int rfc3686_skcipher_setkey(struct crypto_skcipher *skcipher,
				   const u8 *key, unsigned int keylen)
{
	u32 ctx1_iv_off;
	int err;

	/*
	 * RFC3686 specific:
	 *	| CONTEXT1[255:128] = {NONCE, IV, COUNTER}
	 *	| *key = {KEY, NONCE}
	 */
	ctx1_iv_off = 16 + CTR_RFC3686_NONCE_SIZE;
	keylen -= CTR_RFC3686_NONCE_SIZE;

	err = aes_check_keylen(keylen);
	if (err) {
		crypto_skcipher_set_flags(skcipher,
					  CRYPTO_TFM_RES_BAD_KEY_LEN);
		return err;
	}

	return skcipher_setkey(skcipher, key, keylen, ctx1_iv_off);
}