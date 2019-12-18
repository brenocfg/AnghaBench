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
struct mac_tfm_ctx {int /*<<< orphan*/  key; } ;
struct mac_desc_ctx {scalar_t__ len; int /*<<< orphan*/  dg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 struct mac_tfm_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_do_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mac_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int cbcmac_final(struct shash_desc *desc, u8 *out)
{
	struct mac_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	struct mac_desc_ctx *ctx = shash_desc_ctx(desc);

	mac_do_update(&tctx->key, NULL, 0, ctx->dg, (ctx->len != 0), 0);

	memcpy(out, ctx->dg, AES_BLOCK_SIZE);

	return 0;
}