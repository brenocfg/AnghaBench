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
struct crypto_akcipher {int dummy; } ;
struct caam_rsa_ctx {int /*<<< orphan*/  dev; int /*<<< orphan*/  padding_dma; } ;

/* Variables and functions */
 scalar_t__ CAAM_RSA_MAX_INPUT_SIZE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  caam_jr_alloc () ; 
 int /*<<< orphan*/  caam_jr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  zero_buffer ; 

__attribute__((used)) static int caam_rsa_init_tfm(struct crypto_akcipher *tfm)
{
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);

	ctx->dev = caam_jr_alloc();

	if (IS_ERR(ctx->dev)) {
		pr_err("Job Ring Device allocation for transform failed\n");
		return PTR_ERR(ctx->dev);
	}

	ctx->padding_dma = dma_map_single(ctx->dev, zero_buffer,
					  CAAM_RSA_MAX_INPUT_SIZE - 1,
					  DMA_TO_DEVICE);
	if (dma_mapping_error(ctx->dev, ctx->padding_dma)) {
		dev_err(ctx->dev, "unable to map padding\n");
		caam_jr_free(ctx->dev);
		return -ENOMEM;
	}

	return 0;
}