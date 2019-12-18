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
struct crypto_shash {int dummy; } ;
struct cbcmac_tfm_ctx {int /*<<< orphan*/  child; } ;

/* Variables and functions */
 int crypto_cipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct cbcmac_tfm_ctx* crypto_shash_ctx (struct crypto_shash*) ; 

__attribute__((used)) static int crypto_cbcmac_digest_setkey(struct crypto_shash *parent,
				     const u8 *inkey, unsigned int keylen)
{
	struct cbcmac_tfm_ctx *ctx = crypto_shash_ctx(parent);

	return crypto_cipher_setkey(ctx->child, inkey, keylen);
}