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
typedef  scalar_t__ u32 ;
struct sec4_sg_entry {int dummy; } ;
struct caam_hash_ctx {int /*<<< orphan*/  jrdev; } ;
struct ahash_request {int /*<<< orphan*/  src; } ;
struct ahash_edesc {unsigned int sec4_sg_bytes; int /*<<< orphan*/  hw_desc; int /*<<< orphan*/  sec4_sg_dma; struct sec4_sg_entry* sec4_sg; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 scalar_t__ LDST_SGF ; 
 int /*<<< orphan*/  append_seq_in_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,struct sec4_sg_entry*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pad_sg_nents (unsigned int) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_to_sec4_sg_last (int /*<<< orphan*/ ,size_t,struct sec4_sg_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_edesc_add_src(struct caam_hash_ctx *ctx,
			       struct ahash_edesc *edesc,
			       struct ahash_request *req, int nents,
			       unsigned int first_sg,
			       unsigned int first_bytes, size_t to_hash)
{
	dma_addr_t src_dma;
	u32 options;

	if (nents > 1 || first_sg) {
		struct sec4_sg_entry *sg = edesc->sec4_sg;
		unsigned int sgsize = sizeof(*sg) *
				      pad_sg_nents(first_sg + nents);

		sg_to_sec4_sg_last(req->src, to_hash, sg + first_sg, 0);

		src_dma = dma_map_single(ctx->jrdev, sg, sgsize, DMA_TO_DEVICE);
		if (dma_mapping_error(ctx->jrdev, src_dma)) {
			dev_err(ctx->jrdev, "unable to map S/G table\n");
			return -ENOMEM;
		}

		edesc->sec4_sg_bytes = sgsize;
		edesc->sec4_sg_dma = src_dma;
		options = LDST_SGF;
	} else {
		src_dma = sg_dma_address(req->src);
		options = 0;
	}

	append_seq_in_ptr(edesc->hw_desc, src_dma, first_bytes + to_hash,
			  options);

	return 0;
}