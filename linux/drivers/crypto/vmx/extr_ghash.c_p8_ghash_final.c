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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct p8_ghash_desc_ctx {int bytes; int /*<<< orphan*/  shash; scalar_t__* buffer; } ;
struct p8_ghash_ctx {int dummy; } ;

/* Variables and functions */
 int GHASH_DIGEST_SIZE ; 
 int /*<<< orphan*/  __ghash_block (struct p8_ghash_ctx*,struct p8_ghash_desc_ctx*) ; 
 int /*<<< orphan*/  crypto_shash_tfm (int /*<<< orphan*/ ) ; 
 struct p8_ghash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct p8_ghash_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int p8_ghash_final(struct shash_desc *desc, u8 *out)
{
	int i;
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(desc->tfm));
	struct p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	if (dctx->bytes) {
		for (i = dctx->bytes; i < GHASH_DIGEST_SIZE; i++)
			dctx->buffer[i] = 0;
		__ghash_block(ctx, dctx);
		dctx->bytes = 0;
	}
	memcpy(out, dctx->shash, GHASH_DIGEST_SIZE);
	return 0;
}