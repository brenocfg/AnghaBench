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
struct caam_flc {void** flc; int /*<<< orphan*/ * sh_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  keylen; } ;
struct caam_ctx {int /*<<< orphan*/  dir; int /*<<< orphan*/ * flc_dma; int /*<<< orphan*/  authsize; int /*<<< orphan*/  adata; TYPE_1__ cdata; struct caam_flc* flc; struct device* dev; } ;

/* Variables and functions */
 size_t DECRYPT ; 
 size_t ENCRYPT ; 
 int /*<<< orphan*/  cnstr_shdsc_chachapoly (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_caam32 (int /*<<< orphan*/ ) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 int desc_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chachapoly_set_sh_desc(struct crypto_aead *aead)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	unsigned int ivsize = crypto_aead_ivsize(aead);
	struct device *dev = ctx->dev;
	struct caam_flc *flc;
	u32 *desc;

	if (!ctx->cdata.keylen || !ctx->authsize)
		return 0;

	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_chachapoly(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, true, true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_for_device(dev, ctx->flc_dma[ENCRYPT],
				   sizeof(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_chachapoly(desc, &ctx->cdata, &ctx->adata, ivsize,
			       ctx->authsize, false, true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_for_device(dev, ctx->flc_dma[DECRYPT],
				   sizeof(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	return 0;
}