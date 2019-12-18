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
struct sec4_sg_entry {int dummy; } ;
struct rsa_priv_f2_pdb {int sgf; size_t p_q_len; void* d_dma; void* p_dma; void* q_dma; void* tmp1_dma; void* f_dma; void* g_dma; void* tmp2_dma; } ;
struct TYPE_2__ {struct rsa_priv_f2_pdb priv_f2; } ;
struct rsa_edesc {int src_nents; int dst_nents; void* sec4_sg_dma; TYPE_1__ pdb; } ;
struct device {int dummy; } ;
struct crypto_akcipher {int dummy; } ;
struct caam_rsa_req_ctx {int /*<<< orphan*/  fixup_src; } ;
struct caam_rsa_key {size_t p_sz; size_t q_sz; size_t d_sz; int n_sz; int /*<<< orphan*/  tmp2; int /*<<< orphan*/  tmp1; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  d; } ;
struct caam_rsa_ctx {struct device* dev; struct caam_rsa_key key; } ;
struct akcipher_request {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int RSA_PDB_D_SHIFT ; 
 size_t RSA_PDB_Q_SHIFT ; 
 int RSA_PRIV_PDB_SGF_F ; 
 int RSA_PRIV_PDB_SGF_G ; 
 struct caam_rsa_req_ctx* akcipher_request_ctx (struct akcipher_request*) ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* dma_map_single (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,void*,size_t,int /*<<< orphan*/ ) ; 
 void* sg_dma_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_rsa_priv_f2_pdb(struct akcipher_request *req,
			       struct rsa_edesc *edesc)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct caam_rsa_key *key = &ctx->key;
	struct device *dev = ctx->dev;
	struct rsa_priv_f2_pdb *pdb = &edesc->pdb.priv_f2;
	int sec4_sg_index = 0;
	size_t p_sz = key->p_sz;
	size_t q_sz = key->q_sz;

	pdb->d_dma = dma_map_single(dev, key->d, key->d_sz, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, pdb->d_dma)) {
		dev_err(dev, "Unable to map RSA private exponent memory\n");
		return -ENOMEM;
	}

	pdb->p_dma = dma_map_single(dev, key->p, p_sz, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, pdb->p_dma)) {
		dev_err(dev, "Unable to map RSA prime factor p memory\n");
		goto unmap_d;
	}

	pdb->q_dma = dma_map_single(dev, key->q, q_sz, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, pdb->q_dma)) {
		dev_err(dev, "Unable to map RSA prime factor q memory\n");
		goto unmap_p;
	}

	pdb->tmp1_dma = dma_map_single(dev, key->tmp1, p_sz, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, pdb->tmp1_dma)) {
		dev_err(dev, "Unable to map RSA tmp1 memory\n");
		goto unmap_q;
	}

	pdb->tmp2_dma = dma_map_single(dev, key->tmp2, q_sz, DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, pdb->tmp2_dma)) {
		dev_err(dev, "Unable to map RSA tmp2 memory\n");
		goto unmap_tmp1;
	}

	if (edesc->src_nents > 1) {
		pdb->sgf |= RSA_PRIV_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->src_nents;
	} else {
		struct caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);

		pdb->g_dma = sg_dma_address(req_ctx->fixup_src);
	}

	if (edesc->dst_nents > 1) {
		pdb->sgf |= RSA_PRIV_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * sizeof(struct sec4_sg_entry);
	} else {
		pdb->f_dma = sg_dma_address(req->dst);
	}

	pdb->sgf |= (key->d_sz << RSA_PDB_D_SHIFT) | key->n_sz;
	pdb->p_q_len = (q_sz << RSA_PDB_Q_SHIFT) | p_sz;

	return 0;

unmap_tmp1:
	dma_unmap_single(dev, pdb->tmp1_dma, p_sz, DMA_BIDIRECTIONAL);
unmap_q:
	dma_unmap_single(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
unmap_p:
	dma_unmap_single(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);
unmap_d:
	dma_unmap_single(dev, pdb->d_dma, key->d_sz, DMA_TO_DEVICE);

	return -ENOMEM;
}