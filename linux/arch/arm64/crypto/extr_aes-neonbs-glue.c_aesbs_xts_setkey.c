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
struct crypto_aes_ctx {int /*<<< orphan*/  key_enc; } ;
struct aesbs_xts_ctx {int /*<<< orphan*/  twkey; struct crypto_aes_ctx cts; } ;

/* Variables and functions */
 int aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int aesbs_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct aesbs_xts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xts_verify_key (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int aesbs_xts_setkey(struct crypto_skcipher *tfm, const u8 *in_key,
			    unsigned int key_len)
{
	struct aesbs_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_aes_ctx rk;
	int err;

	err = xts_verify_key(tfm, in_key, key_len);
	if (err)
		return err;

	key_len /= 2;
	err = aes_expandkey(&ctx->cts, in_key, key_len);
	if (err)
		return err;

	err = aes_expandkey(&rk, in_key + key_len, key_len);
	if (err)
		return err;

	memcpy(ctx->twkey, rk.key_enc, sizeof(ctx->twkey));

	return aesbs_setkey(tfm, in_key, key_len);
}