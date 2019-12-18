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
struct mv_cesa_des_ctx {int /*<<< orphan*/  key; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DES3_EDE_KEY_SIZE ; 
 struct mv_cesa_des_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int verify_skcipher_des3_key (struct crypto_skcipher*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int mv_cesa_des3_ede_setkey(struct crypto_skcipher *cipher,
				   const u8 *key, unsigned int len)
{
	struct mv_cesa_des_ctx *ctx = crypto_skcipher_ctx(cipher);
	int err;

	err = verify_skcipher_des3_key(cipher, key);
	if (err)
		return err;

	memcpy(ctx->key, key, DES3_EDE_KEY_SIZE);

	return 0;
}