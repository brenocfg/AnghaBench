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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  keylen; } ;
struct caam_ctx {int /*<<< orphan*/  dir; int /*<<< orphan*/  sh_desc_dec_dma; int /*<<< orphan*/  authsize; int /*<<< orphan*/  adata; TYPE_1__ cdata; int /*<<< orphan*/ * sh_desc_dec; int /*<<< orphan*/  sh_desc_enc_dma; int /*<<< orphan*/ * sh_desc_enc; struct device* jrdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cnstr_shdsc_chachapoly (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int,int) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  desc_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chachapoly_set_sh_desc(struct crypto_aead *aead)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct device *jrdev = ctx->jrdev;
	unsigned int ivsize = crypto_aead_ivsize(aead);
	u32 *desc;

	if (!ctx->cdata.keylen || !ctx->authsize)
		return 0;

	desc = ctx->sh_desc_enc;
	cnstr_shdsc_chachapoly(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, true, false);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_enc_dma,
				   desc_bytes(desc), ctx->dir);

	desc = ctx->sh_desc_dec;
	cnstr_shdsc_chachapoly(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, false, false);
	dma_sync_single_for_device(jrdev, ctx->sh_desc_dec_dma,
				   desc_bytes(desc), ctx->dir);

	return 0;
}