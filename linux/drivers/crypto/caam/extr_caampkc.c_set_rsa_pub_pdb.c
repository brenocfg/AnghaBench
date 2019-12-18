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
struct rsa_pub_pdb {int sgf; int /*<<< orphan*/  f_len; void* g_dma; void* f_dma; void* n_dma; void* e_dma; } ;
struct TYPE_2__ {struct rsa_pub_pdb pub; } ;
struct rsa_edesc {int src_nents; int dst_nents; void* sec4_sg_dma; TYPE_1__ pdb; } ;
struct device {int dummy; } ;
struct crypto_akcipher {int dummy; } ;
struct caam_rsa_req_ctx {int /*<<< orphan*/  fixup_src_len; int /*<<< orphan*/  fixup_src; } ;
struct caam_rsa_key {int n_sz; int e_sz; int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;
struct caam_rsa_ctx {struct device* dev; struct caam_rsa_key key; } ;
struct akcipher_request {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int RSA_PDB_E_SHIFT ; 
 int RSA_PDB_SGF_F ; 
 int RSA_PDB_SGF_G ; 
 struct caam_rsa_req_ctx* akcipher_request_ctx (struct akcipher_request*) ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* dma_map_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 void* sg_dma_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_rsa_pub_pdb(struct akcipher_request *req,
			   struct rsa_edesc *edesc)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct caam_rsa_key *key = &ctx->key;
	struct device *dev = ctx->dev;
	struct rsa_pub_pdb *pdb = &edesc->pdb.pub;
	int sec4_sg_index = 0;

	pdb->n_dma = dma_map_single(dev, key->n, key->n_sz, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, pdb->n_dma)) {
		dev_err(dev, "Unable to map RSA modulus memory\n");
		return -ENOMEM;
	}

	pdb->e_dma = dma_map_single(dev, key->e, key->e_sz, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, pdb->e_dma)) {
		dev_err(dev, "Unable to map RSA public exponent memory\n");
		dma_unmap_single(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
		return -ENOMEM;
	}

	if (edesc->src_nents > 1) {
		pdb->sgf |= RSA_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->src_nents;
	} else {
		pdb->f_dma = sg_dma_address(req_ctx->fixup_src);
	}

	if (edesc->dst_nents > 1) {
		pdb->sgf |= RSA_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * sizeof(struct sec4_sg_entry);
	} else {
		pdb->g_dma = sg_dma_address(req->dst);
	}

	pdb->sgf |= (key->e_sz << RSA_PDB_E_SHIFT) | key->n_sz;
	pdb->f_len = req_ctx->fixup_src_len;

	return 0;
}