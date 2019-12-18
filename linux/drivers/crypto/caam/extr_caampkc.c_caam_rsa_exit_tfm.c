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
struct caam_rsa_key {int dummy; } ;
struct caam_rsa_ctx {int /*<<< orphan*/  dev; int /*<<< orphan*/  padding_dma; struct caam_rsa_key key; } ;

/* Variables and functions */
 scalar_t__ CAAM_RSA_MAX_INPUT_SIZE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  caam_jr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caam_rsa_free_key (struct caam_rsa_key*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void caam_rsa_exit_tfm(struct crypto_akcipher *tfm)
{
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct caam_rsa_key *key = &ctx->key;

	dma_unmap_single(ctx->dev, ctx->padding_dma, CAAM_RSA_MAX_INPUT_SIZE -
			 1, DMA_TO_DEVICE);
	caam_rsa_free_key(key);
	caam_jr_free(ctx->dev);
}