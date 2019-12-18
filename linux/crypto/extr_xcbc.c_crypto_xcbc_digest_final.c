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
typedef  int u8 ;
struct xcbc_tfm_ctx {int /*<<< orphan*/ * ctx; struct crypto_cipher* child; } ;
struct xcbc_desc_ctx {int len; int /*<<< orphan*/ * ctx; } ;
struct shash_desc {struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int* PTR_ALIGN (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int*,int*) ; 
 unsigned long crypto_shash_alignmask (struct crypto_shash*) ; 
 int crypto_shash_blocksize (struct crypto_shash*) ; 
 struct xcbc_tfm_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_xor (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 
 struct xcbc_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int crypto_xcbc_digest_final(struct shash_desc *pdesc, u8 *out)
{
	struct crypto_shash *parent = pdesc->tfm;
	unsigned long alignmask = crypto_shash_alignmask(parent);
	struct xcbc_tfm_ctx *tctx = crypto_shash_ctx(parent);
	struct xcbc_desc_ctx *ctx = shash_desc_ctx(pdesc);
	struct crypto_cipher *tfm = tctx->child;
	int bs = crypto_shash_blocksize(parent);
	u8 *consts = PTR_ALIGN(&tctx->ctx[0], alignmask + 1);
	u8 *odds = PTR_ALIGN(&ctx->ctx[0], alignmask + 1);
	u8 *prev = odds + bs;
	unsigned int offset = 0;

	if (ctx->len != bs) {
		unsigned int rlen;
		u8 *p = odds + ctx->len;

		*p = 0x80;
		p++;

		rlen = bs - ctx->len -1;
		if (rlen)
			memset(p, 0, rlen);

		offset += bs;
	}

	crypto_xor(prev, odds, bs);
	crypto_xor(prev, consts + offset, bs);

	crypto_cipher_encrypt_one(tfm, out, prev);

	return 0;
}