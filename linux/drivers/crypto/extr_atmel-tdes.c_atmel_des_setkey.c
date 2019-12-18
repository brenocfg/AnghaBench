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
struct crypto_ablkcipher {int dummy; } ;
struct atmel_tdes_ctx {unsigned int keylen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 struct atmel_tdes_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int verify_ablkcipher_des_key (struct crypto_ablkcipher*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int atmel_des_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
			   unsigned int keylen)
{
	struct atmel_tdes_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	int err;

	err = verify_ablkcipher_des_key(tfm, key);
	if (err)
		return err;

	memcpy(ctx->key, key, keylen);
	ctx->keylen = keylen;

	return 0;
}