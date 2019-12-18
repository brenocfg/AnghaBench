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
typedef  int /*<<< orphan*/  const u8 ;
struct xcbc_tfm_ctx {int /*<<< orphan*/  child; int /*<<< orphan*/ * ctx; } ;
struct crypto_shash {int dummy; } ;
typedef  int /*<<< orphan*/  key1 ;

/* Variables and functions */
 int /*<<< orphan*/  const* PTR_ALIGN (int /*<<< orphan*/ *,unsigned long) ; 
 int XCBC_BLOCKSIZE ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int crypto_cipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 unsigned long crypto_shash_alignmask (struct crypto_shash*) ; 
 struct xcbc_tfm_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 scalar_t__ ks ; 

__attribute__((used)) static int crypto_xcbc_digest_setkey(struct crypto_shash *parent,
				     const u8 *inkey, unsigned int keylen)
{
	unsigned long alignmask = crypto_shash_alignmask(parent);
	struct xcbc_tfm_ctx *ctx = crypto_shash_ctx(parent);
	u8 *consts = PTR_ALIGN(&ctx->ctx[0], alignmask + 1);
	int err = 0;
	u8 key1[XCBC_BLOCKSIZE];
	int bs = sizeof(key1);

	if ((err = crypto_cipher_setkey(ctx->child, inkey, keylen)))
		return err;

	crypto_cipher_encrypt_one(ctx->child, consts, (u8 *)ks + bs);
	crypto_cipher_encrypt_one(ctx->child, consts + bs, (u8 *)ks + bs * 2);
	crypto_cipher_encrypt_one(ctx->child, key1, (u8 *)ks);

	return crypto_cipher_setkey(ctx->child, key1, bs);

}