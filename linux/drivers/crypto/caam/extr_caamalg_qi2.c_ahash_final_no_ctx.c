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
typedef  int /*<<< orphan*/  u8 ;
struct dpaa2_fl_entry {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct caam_request {struct ahash_edesc* edesc; TYPE_1__* ctx; int /*<<< orphan*/  cbk; int /*<<< orphan*/  flc_dma; int /*<<< orphan*/ * flc; struct dpaa2_fl_entry* fd_flt; } ;
struct caam_hash_state {int ctx_dma_len; void* ctx_dma; void* buf_dma; int /*<<< orphan*/ * caam_ctx; struct caam_request caam_req; } ;
struct caam_hash_ctx {int /*<<< orphan*/  dev; int /*<<< orphan*/ * flc_dma; int /*<<< orphan*/ * flc; } ;
struct TYPE_2__ {int flags; } ;
struct ahash_request {TYPE_1__ base; } ;
struct ahash_edesc {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 size_t DIGEST ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  ahash_done ; 
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_unmap_ctx (int /*<<< orphan*/ ,struct ahash_edesc*,struct ahash_request*,int /*<<< orphan*/ ) ; 
 struct caam_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/ * current_buf (struct caam_hash_state*) ; 
 int* current_buflen (struct caam_hash_state*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int dpaa2_caam_enqueue (int /*<<< orphan*/ ,struct caam_request*) ; 
 int /*<<< orphan*/  dpaa2_fl_set_addr (struct dpaa2_fl_entry*,void*) ; 
 int /*<<< orphan*/  dpaa2_fl_set_final (struct dpaa2_fl_entry*,int) ; 
 int /*<<< orphan*/  dpaa2_fl_set_format (struct dpaa2_fl_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_fl_set_len (struct dpaa2_fl_entry*,int) ; 
 int /*<<< orphan*/  dpaa2_fl_single ; 
 int /*<<< orphan*/  memset (struct dpaa2_fl_entry**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qi_cache_free (struct ahash_edesc*) ; 
 struct ahash_edesc* qi_cache_zalloc (int) ; 

__attribute__((used)) static int ahash_final_no_ctx(struct ahash_request *req)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct caam_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	struct caam_hash_state *state = ahash_request_ctx(req);
	struct caam_request *req_ctx = &state->caam_req;
	struct dpaa2_fl_entry *in_fle = &req_ctx->fd_flt[1];
	struct dpaa2_fl_entry *out_fle = &req_ctx->fd_flt[0];
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	u8 *buf = current_buf(state);
	int buflen = *current_buflen(state);
	int digestsize = crypto_ahash_digestsize(ahash);
	struct ahash_edesc *edesc;
	int ret = -ENOMEM;

	/* allocate space for base edesc and link tables */
	edesc = qi_cache_zalloc(GFP_DMA | flags);
	if (!edesc)
		return ret;

	if (buflen) {
		state->buf_dma = dma_map_single(ctx->dev, buf, buflen,
						DMA_TO_DEVICE);
		if (dma_mapping_error(ctx->dev, state->buf_dma)) {
			dev_err(ctx->dev, "unable to map src\n");
			goto unmap;
		}
	}

	state->ctx_dma_len = digestsize;
	state->ctx_dma = dma_map_single(ctx->dev, state->caam_ctx, digestsize,
					DMA_FROM_DEVICE);
	if (dma_mapping_error(ctx->dev, state->ctx_dma)) {
		dev_err(ctx->dev, "unable to map ctx\n");
		state->ctx_dma = 0;
		goto unmap;
	}

	memset(&req_ctx->fd_flt, 0, sizeof(req_ctx->fd_flt));
	dpaa2_fl_set_final(in_fle, true);
	/*
	 * crypto engine requires the input entry to be present when
	 * "frame list" FD is used.
	 * Since engine does not support FMT=2'b11 (unused entry type), leaving
	 * in_fle zeroized (except for "Final" flag) is the best option.
	 */
	if (buflen) {
		dpaa2_fl_set_format(in_fle, dpaa2_fl_single);
		dpaa2_fl_set_addr(in_fle, state->buf_dma);
		dpaa2_fl_set_len(in_fle, buflen);
	}
	dpaa2_fl_set_format(out_fle, dpaa2_fl_single);
	dpaa2_fl_set_addr(out_fle, state->ctx_dma);
	dpaa2_fl_set_len(out_fle, digestsize);

	req_ctx->flc = &ctx->flc[DIGEST];
	req_ctx->flc_dma = ctx->flc_dma[DIGEST];
	req_ctx->cbk = ahash_done;
	req_ctx->ctx = &req->base;
	req_ctx->edesc = edesc;

	ret = dpaa2_caam_enqueue(ctx->dev, req_ctx);
	if (ret == -EINPROGRESS ||
	    (ret == -EBUSY && req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
		return ret;

unmap:
	ahash_unmap_ctx(ctx->dev, edesc, req, DMA_FROM_DEVICE);
	qi_cache_free(edesc);
	return ret;
}