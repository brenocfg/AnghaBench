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
struct spacc_ablk_ctx {unsigned int key_len; int /*<<< orphan*/  key; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 struct spacc_ablk_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int verify_ablkcipher_des3_key (struct crypto_ablkcipher*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int spacc_des3_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			     unsigned int len)
{
	struct spacc_ablk_ctx *ctx = crypto_ablkcipher_ctx(cipher);
	int err;

	err = verify_ablkcipher_des3_key(cipher, key);
	if (err)
		return err;

	memcpy(ctx->key, key, len);
	ctx->key_len = len;

	return 0;
}