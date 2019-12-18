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
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_NEED_KEY ; 
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_MASK ; 
 int /*<<< orphan*/  crypto_ablkcipher_clear_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 
 int crypto_ablkcipher_get_flags (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int) ; 
 int crypto_ablkcipher_setkey (struct crypto_ablkcipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_skcipher_clear_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 struct crypto_ablkcipher** crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_get_flags (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int) ; 
 int /*<<< orphan*/  skcipher_set_needkey (struct crypto_skcipher*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int skcipher_setkey_ablkcipher(struct crypto_skcipher *tfm,
				      const u8 *key, unsigned int keylen)
{
	struct crypto_ablkcipher **ctx = crypto_skcipher_ctx(tfm);
	struct crypto_ablkcipher *ablkcipher = *ctx;
	int err;

	crypto_ablkcipher_clear_flags(ablkcipher, ~0);
	crypto_ablkcipher_set_flags(ablkcipher,
				    crypto_skcipher_get_flags(tfm) &
				    CRYPTO_TFM_REQ_MASK);
	err = crypto_ablkcipher_setkey(ablkcipher, key, keylen);
	crypto_skcipher_set_flags(tfm,
				  crypto_ablkcipher_get_flags(ablkcipher) &
				  CRYPTO_TFM_RES_MASK);
	if (unlikely(err)) {
		skcipher_set_needkey(tfm);
		return err;
	}

	crypto_skcipher_clear_flags(tfm, CRYPTO_TFM_NEED_KEY);
	return 0;
}