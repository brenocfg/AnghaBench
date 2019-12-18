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
struct crypto_skcipher {int dummy; } ;
struct crypto_aes_ctx {int /*<<< orphan*/  key_enc; } ;
struct TYPE_2__ {int rounds; int /*<<< orphan*/  rk; } ;
struct aesbs_cbc_ctx {TYPE_1__ key; int /*<<< orphan*/  enc; } ;

/* Variables and functions */
 int aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  aesbs_convert_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct aesbs_cbc_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aesbs_cbc_setkey(struct crypto_skcipher *tfm, const u8 *in_key,
			    unsigned int key_len)
{
	struct aesbs_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_aes_ctx rk;
	int err;

	err = aes_expandkey(&rk, in_key, key_len);
	if (err)
		return err;

	ctx->key.rounds = 6 + key_len / 4;

	memcpy(ctx->enc, rk.key_enc, sizeof(ctx->enc));

	kernel_neon_begin();
	aesbs_convert_key(ctx->key.rk, rk.key_enc, ctx->key.rounds);
	kernel_neon_end();

	return 0;
}