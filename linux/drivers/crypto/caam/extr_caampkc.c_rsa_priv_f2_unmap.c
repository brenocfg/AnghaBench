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
struct rsa_priv_f2_pdb {int /*<<< orphan*/  tmp2_dma; int /*<<< orphan*/  tmp1_dma; int /*<<< orphan*/  q_dma; int /*<<< orphan*/  p_dma; int /*<<< orphan*/  d_dma; } ;
struct TYPE_2__ {struct rsa_priv_f2_pdb priv_f2; } ;
struct rsa_edesc {TYPE_1__ pdb; } ;
struct device {int dummy; } ;
struct crypto_akcipher {int dummy; } ;
struct caam_rsa_key {size_t p_sz; size_t q_sz; size_t d_sz; } ;
struct caam_rsa_ctx {struct caam_rsa_key key; } ;
struct akcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsa_priv_f2_unmap(struct device *dev, struct rsa_edesc *edesc,
			      struct akcipher_request *req)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct caam_rsa_key *key = &ctx->key;
	struct rsa_priv_f2_pdb *pdb = &edesc->pdb.priv_f2;
	size_t p_sz = key->p_sz;
	size_t q_sz = key->q_sz;

	dma_unmap_single(dev, pdb->d_dma, key->d_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
	dma_unmap_single(dev, pdb->tmp1_dma, p_sz, DMA_BIDIRECTIONAL);
	dma_unmap_single(dev, pdb->tmp2_dma, q_sz, DMA_BIDIRECTIONAL);
}