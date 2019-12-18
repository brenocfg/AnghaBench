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
struct qce_cipher_ctx {unsigned int enc_keylen; int /*<<< orphan*/  enc_key; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 struct qce_cipher_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int verify_ablkcipher_des_key (struct crypto_ablkcipher*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int qce_des_setkey(struct crypto_ablkcipher *ablk, const u8 *key,
			  unsigned int keylen)
{
	struct qce_cipher_ctx *ctx = crypto_ablkcipher_ctx(ablk);
	int err;

	err = verify_ablkcipher_des_key(ablk, key);
	if (err)
		return err;

	ctx->enc_keylen = keylen;
	memcpy(ctx->enc_key, key, keylen);
	return 0;
}