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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {size_t offset; size_t length; } ;
struct atmel_sha_reqctx {size_t block_size; } ;
struct atmel_sha_dma {int nents; size_t last_sg_length; } ;
struct atmel_sha_dev {struct ahash_request* req; struct atmel_sha_dma dma_lch_in; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int /*<<< orphan*/  IS_ALIGNED (size_t,size_t) ; 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static bool atmel_sha_dma_check_aligned(struct atmel_sha_dev *dd,
					struct scatterlist *sg,
					size_t len)
{
	struct atmel_sha_dma *dma = &dd->dma_lch_in;
	struct ahash_request *req = dd->req;
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	size_t bs = ctx->block_size;
	int nents;

	for (nents = 0; sg; sg = sg_next(sg), ++nents) {
		if (!IS_ALIGNED(sg->offset, sizeof(u32)))
			return false;

		/*
		 * This is the last sg, the only one that is allowed to
		 * have an unaligned length.
		 */
		if (len <= sg->length) {
			dma->nents = nents + 1;
			dma->last_sg_length = sg->length;
			sg->length = ALIGN(len, sizeof(u32));
			return true;
		}

		/* All other sg lengths MUST be aligned to the block size. */
		if (!IS_ALIGNED(sg->length, bs))
			return false;

		len -= sg->length;
	}

	return false;
}