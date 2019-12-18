#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypto_ablkcipher {int dummy; } ;
struct TYPE_2__ {unsigned int keylen; int /*<<< orphan*/  key; } ;
struct atmel_aes_xts_ctx {TYPE_1__ base; int /*<<< orphan*/  key2; } ;

/* Variables and functions */
 struct atmel_aes_xts_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int xts_check_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int atmel_aes_xts_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
				unsigned int keylen)
{
	struct atmel_aes_xts_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	int err;

	err = xts_check_key(crypto_ablkcipher_tfm(tfm), key, keylen);
	if (err)
		return err;

	memcpy(ctx->base.key, key, keylen/2);
	memcpy(ctx->key2, key + keylen/2, keylen/2);
	ctx->base.keylen = keylen/2;

	return 0;
}