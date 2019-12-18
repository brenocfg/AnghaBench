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
struct priv {struct crypto_skcipher* child; struct crypto_cipher* tweak; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_cipher_clear_flags (struct crypto_cipher*,int) ; 
 int crypto_cipher_get_flags (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto_cipher_set_flags (struct crypto_cipher*,int) ; 
 int crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_skcipher_clear_flags (struct crypto_skcipher*,int) ; 
 struct priv* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_get_flags (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int) ; 
 int crypto_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 int xts_verify_key (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int setkey(struct crypto_skcipher *parent, const u8 *key,
		  unsigned int keylen)
{
	struct priv *ctx = crypto_skcipher_ctx(parent);
	struct crypto_skcipher *child;
	struct crypto_cipher *tweak;
	int err;

	err = xts_verify_key(parent, key, keylen);
	if (err)
		return err;

	keylen /= 2;

	/* we need two cipher instances: one to compute the initial 'tweak'
	 * by encrypting the IV (usually the 'plain' iv) and the other
	 * one to encrypt and decrypt the data */

	/* tweak cipher, uses Key2 i.e. the second half of *key */
	tweak = ctx->tweak;
	crypto_cipher_clear_flags(tweak, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(tweak, crypto_skcipher_get_flags(parent) &
				       CRYPTO_TFM_REQ_MASK);
	err = crypto_cipher_setkey(tweak, key + keylen, keylen);
	crypto_skcipher_set_flags(parent, crypto_cipher_get_flags(tweak) &
					  CRYPTO_TFM_RES_MASK);
	if (err)
		return err;

	/* data cipher, uses Key1 i.e. the first half of *key */
	child = ctx->child;
	crypto_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(child, crypto_skcipher_get_flags(parent) &
					 CRYPTO_TFM_REQ_MASK);
	err = crypto_skcipher_setkey(child, key, keylen);
	crypto_skcipher_set_flags(parent, crypto_skcipher_get_flags(child) &
					  CRYPTO_TFM_RES_MASK);

	return err;
}