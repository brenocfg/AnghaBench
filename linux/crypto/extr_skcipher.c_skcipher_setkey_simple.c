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
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_cipher_clear_flags (struct crypto_cipher*,int) ; 
 int crypto_cipher_get_flags (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto_cipher_set_flags (struct crypto_cipher*,int) ; 
 int crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 int crypto_skcipher_get_flags (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int) ; 
 struct crypto_cipher* skcipher_cipher_simple (struct crypto_skcipher*) ; 

__attribute__((used)) static int skcipher_setkey_simple(struct crypto_skcipher *tfm, const u8 *key,
				  unsigned int keylen)
{
	struct crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	int err;

	crypto_cipher_clear_flags(cipher, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(cipher, crypto_skcipher_get_flags(tfm) &
				CRYPTO_TFM_REQ_MASK);
	err = crypto_cipher_setkey(cipher, key, keylen);
	crypto_skcipher_set_flags(tfm, crypto_cipher_get_flags(cipher) &
				  CRYPTO_TFM_RES_MASK);
	return err;
}