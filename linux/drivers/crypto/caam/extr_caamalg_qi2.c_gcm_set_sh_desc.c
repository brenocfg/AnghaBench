#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct caam_flc {void** flc; int /*<<< orphan*/ * sh_desc; } ;
struct TYPE_3__ {int keylen; int key_inline; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key_virt; } ;
struct caam_ctx {int /*<<< orphan*/  dir; int /*<<< orphan*/ * flc_dma; int /*<<< orphan*/  authsize; TYPE_1__ cdata; struct caam_flc* flc; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key; struct device* dev; } ;

/* Variables and functions */
 int CAAM_DESC_BYTES_MAX ; 
 size_t DECRYPT ; 
 int DESC_JOB_IO_LEN ; 
 int DESC_QI_GCM_DEC_LEN ; 
 int DESC_QI_GCM_ENC_LEN ; 
 size_t ENCRYPT ; 
 int /*<<< orphan*/  cnstr_shdsc_gcm_decap (int /*<<< orphan*/ *,TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cnstr_shdsc_gcm_encap (int /*<<< orphan*/ *,TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_caam32 (int /*<<< orphan*/ ) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 int desc_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gcm_set_sh_desc(struct crypto_aead *aead)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct device *dev = ctx->dev;
	unsigned int ivsize = crypto_aead_ivsize(aead);
	struct caam_flc *flc;
	u32 *desc;
	int rem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	if (!ctx->cdata.keylen || !ctx->authsize)
		return 0;

	/*
	 * AES GCM encrypt shared descriptor
	 * Job Descriptor and Shared Descriptor
	 * must fit into the 64-word Descriptor h/w Buffer
	 */
	if (rem_bytes >= DESC_QI_GCM_ENC_LEN) {
		ctx->cdata.key_inline = true;
		ctx->cdata.key_virt = ctx->key;
	} else {
		ctx->cdata.key_inline = false;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	flc = &ctx->flc[ENCRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_gcm_encap(desc, &ctx->cdata, ivsize, ctx->authsize, true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_for_device(dev, ctx->flc_dma[ENCRYPT],
				   sizeof(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	/*
	 * Job Descriptor and Shared Descriptors
	 * must all fit into the 64-word Descriptor h/w Buffer
	 */
	if (rem_bytes >= DESC_QI_GCM_DEC_LEN) {
		ctx->cdata.key_inline = true;
		ctx->cdata.key_virt = ctx->key;
	} else {
		ctx->cdata.key_inline = false;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	flc = &ctx->flc[DECRYPT];
	desc = flc->sh_desc;
	cnstr_shdsc_gcm_decap(desc, &ctx->cdata, ivsize, ctx->authsize, true);
	flc->flc[1] = cpu_to_caam32(desc_len(desc)); /* SDL */
	dma_sync_single_for_device(dev, ctx->flc_dma[DECRYPT],
				   sizeof(flc->flc) + desc_bytes(desc),
				   ctx->dir);

	return 0;
}