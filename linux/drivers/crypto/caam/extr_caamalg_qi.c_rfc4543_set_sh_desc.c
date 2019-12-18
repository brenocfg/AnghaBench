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
struct crypto_aead {int dummy; } ;
struct TYPE_3__ {int keylen; int key_inline; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  key_virt; } ;
struct caam_ctx {int /*<<< orphan*/  authsize; TYPE_1__ cdata; int /*<<< orphan*/  sh_desc_dec; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  sh_desc_enc; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int CAAM_DESC_BYTES_MAX ; 
 int DESC_JOB_IO_LEN ; 
 int DESC_QI_RFC4543_DEC_LEN ; 
 int DESC_QI_RFC4543_ENC_LEN ; 
 int /*<<< orphan*/  cnstr_shdsc_rfc4543_decap (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cnstr_shdsc_rfc4543_encap (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 

__attribute__((used)) static int rfc4543_set_sh_desc(struct crypto_aead *aead)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	unsigned int ivsize = crypto_aead_ivsize(aead);
	int rem_bytes = CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN -
			ctx->cdata.keylen;

	if (!ctx->cdata.keylen || !ctx->authsize)
		return 0;

	ctx->cdata.key_virt = ctx->key;

	/*
	 * Job Descriptor and Shared Descriptor
	 * must fit into the 64-word Descriptor h/w Buffer
	 */
	if (rem_bytes >= DESC_QI_RFC4543_ENC_LEN) {
		ctx->cdata.key_inline = true;
	} else {
		ctx->cdata.key_inline = false;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	cnstr_shdsc_rfc4543_encap(ctx->sh_desc_enc, &ctx->cdata, ivsize,
				  ctx->authsize, true);

	/*
	 * Job Descriptor and Shared Descriptor
	 * must fit into the 64-word Descriptor h/w Buffer
	 */
	if (rem_bytes >= DESC_QI_RFC4543_DEC_LEN) {
		ctx->cdata.key_inline = true;
	} else {
		ctx->cdata.key_inline = false;
		ctx->cdata.key_dma = ctx->key_dma;
	}

	cnstr_shdsc_rfc4543_decap(ctx->sh_desc_dec, &ctx->cdata, ivsize,
				  ctx->authsize, true);

	return 0;
}