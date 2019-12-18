#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_17__ {TYPE_3__* first; TYPE_2__* last; } ;
struct mv_cesa_req {TYPE_4__ chain; } ;
struct mv_cesa_op_ctx {int dummy; } ;
struct mv_cesa_ahash_req {scalar_t__ src_nents; scalar_t__ cache_ptr; scalar_t__ last_req; int /*<<< orphan*/  op_tmpl; struct mv_cesa_req base; } ;
struct TYPE_18__ {unsigned int op_len; scalar_t__ len; } ;
struct TYPE_19__ {scalar_t__ sg; } ;
struct mv_cesa_ahash_dma_iter {TYPE_6__ base; TYPE_7__ src; } ;
struct TYPE_14__ {int flags; } ;
struct ahash_request {int /*<<< orphan*/  src; scalar_t__ nbytes; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_16__ {int /*<<< orphan*/  flags; } ;
struct TYPE_15__ {int flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CESA_TDMA_BREAK_CHAIN ; 
 int CESA_TDMA_END_OF_REQ ; 
 int CESA_TDMA_RESULT ; 
 int /*<<< orphan*/  CESA_TDMA_SET_STATE ; 
 int CESA_TDMA_TYPE_MSK ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mv_cesa_op_ctx*) ; 
 int PTR_ERR (struct mv_cesa_op_ctx*) ; 
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 TYPE_12__* cesa_dev ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int mv_cesa_ahash_dma_add_cache (TYPE_4__*,struct mv_cesa_ahash_req*,int /*<<< orphan*/ ) ; 
 struct mv_cesa_op_ctx* mv_cesa_ahash_dma_last_req (TYPE_4__*,struct mv_cesa_ahash_dma_iter*,struct mv_cesa_ahash_req*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_ahash_last_cleanup (struct ahash_request*) ; 
 int /*<<< orphan*/  mv_cesa_ahash_req_iter_init (struct mv_cesa_ahash_dma_iter*,struct ahash_request*) ; 
 int /*<<< orphan*/  mv_cesa_ahash_req_iter_next_op (struct mv_cesa_ahash_dma_iter*) ; 
 int mv_cesa_dma_add_dummy_end (TYPE_4__*,int /*<<< orphan*/ ) ; 
 struct mv_cesa_op_ctx* mv_cesa_dma_add_frag (TYPE_4__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int mv_cesa_dma_add_op_transfers (TYPE_4__*,TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_dma_cleanup (struct mv_cesa_req*) ; 
 int /*<<< orphan*/  mv_cesa_mac_op_is_first_frag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_cesa_tdma_desc_iter_init (TYPE_4__*) ; 

__attribute__((used)) static int mv_cesa_ahash_dma_req_init(struct ahash_request *req)
{
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		      GFP_KERNEL : GFP_ATOMIC;
	struct mv_cesa_req *basereq = &creq->base;
	struct mv_cesa_ahash_dma_iter iter;
	struct mv_cesa_op_ctx *op = NULL;
	unsigned int frag_len;
	bool set_state = false;
	int ret;
	u32 type;

	basereq->chain.first = NULL;
	basereq->chain.last = NULL;

	if (!mv_cesa_mac_op_is_first_frag(&creq->op_tmpl))
		set_state = true;

	if (creq->src_nents) {
		ret = dma_map_sg(cesa_dev->dev, req->src, creq->src_nents,
				 DMA_TO_DEVICE);
		if (!ret) {
			ret = -ENOMEM;
			goto err;
		}
	}

	mv_cesa_tdma_desc_iter_init(&basereq->chain);
	mv_cesa_ahash_req_iter_init(&iter, req);

	/*
	 * Add the cache (left-over data from a previous block) first.
	 * This will never overflow the SRAM size.
	 */
	ret = mv_cesa_ahash_dma_add_cache(&basereq->chain, creq, flags);
	if (ret)
		goto err_free_tdma;

	if (iter.src.sg) {
		/*
		 * Add all the new data, inserting an operation block and
		 * launch command between each full SRAM block-worth of
		 * data. We intentionally do not add the final op block.
		 */
		while (true) {
			ret = mv_cesa_dma_add_op_transfers(&basereq->chain,
							   &iter.base,
							   &iter.src, flags);
			if (ret)
				goto err_free_tdma;

			frag_len = iter.base.op_len;

			if (!mv_cesa_ahash_req_iter_next_op(&iter))
				break;

			op = mv_cesa_dma_add_frag(&basereq->chain, &creq->op_tmpl,
						  frag_len, flags);
			if (IS_ERR(op)) {
				ret = PTR_ERR(op);
				goto err_free_tdma;
			}
		}
	} else {
		/* Account for the data that was in the cache. */
		frag_len = iter.base.op_len;
	}

	/*
	 * At this point, frag_len indicates whether we have any data
	 * outstanding which needs an operation.  Queue up the final
	 * operation, which depends whether this is the final request.
	 */
	if (creq->last_req)
		op = mv_cesa_ahash_dma_last_req(&basereq->chain, &iter, creq,
						frag_len, flags);
	else if (frag_len)
		op = mv_cesa_dma_add_frag(&basereq->chain, &creq->op_tmpl,
					  frag_len, flags);

	if (IS_ERR(op)) {
		ret = PTR_ERR(op);
		goto err_free_tdma;
	}

	/*
	 * If results are copied via DMA, this means that this
	 * request can be directly processed by the engine,
	 * without partial updates. So we can chain it at the
	 * DMA level with other requests.
	 */
	type = basereq->chain.last->flags & CESA_TDMA_TYPE_MSK;

	if (op && type != CESA_TDMA_RESULT) {
		/* Add dummy desc to wait for crypto operation end */
		ret = mv_cesa_dma_add_dummy_end(&basereq->chain, flags);
		if (ret)
			goto err_free_tdma;
	}

	if (!creq->last_req)
		creq->cache_ptr = req->nbytes + creq->cache_ptr -
				  iter.base.len;
	else
		creq->cache_ptr = 0;

	basereq->chain.last->flags |= CESA_TDMA_END_OF_REQ;

	if (type != CESA_TDMA_RESULT)
		basereq->chain.last->flags |= CESA_TDMA_BREAK_CHAIN;

	if (set_state) {
		/*
		 * Put the CESA_TDMA_SET_STATE flag on the first tdma desc to
		 * let the step logic know that the IVDIG registers should be
		 * explicitly set before launching a TDMA chain.
		 */
		basereq->chain.first->flags |= CESA_TDMA_SET_STATE;
	}

	return 0;

err_free_tdma:
	mv_cesa_dma_cleanup(basereq);
	dma_unmap_sg(cesa_dev->dev, req->src, creq->src_nents, DMA_TO_DEVICE);

err:
	mv_cesa_ahash_last_cleanup(req);

	return ret;
}