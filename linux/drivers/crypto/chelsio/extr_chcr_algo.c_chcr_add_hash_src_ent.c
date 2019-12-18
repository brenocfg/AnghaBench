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
struct ulptx_walk {int /*<<< orphan*/  last_sg_len; int /*<<< orphan*/  last_sg; } ;
struct ulptx_sgl {int dummy; } ;
struct hash_wr_param {int /*<<< orphan*/  sg_len; int /*<<< orphan*/  bfr_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  src_ofst; int /*<<< orphan*/  srcsg; int /*<<< orphan*/  dma_addr; scalar_t__ imm; } ;
struct chcr_ahash_req_ctx {TYPE_1__ hctx_wr; int /*<<< orphan*/  reqbfr; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct chcr_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulptx_walk_add_page (struct ulptx_walk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulptx_walk_add_sg (struct ulptx_walk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulptx_walk_end (struct ulptx_walk*) ; 
 int /*<<< orphan*/  ulptx_walk_init (struct ulptx_walk*,struct ulptx_sgl*) ; 

void chcr_add_hash_src_ent(struct ahash_request *req,
			   struct ulptx_sgl *ulptx,
			   struct hash_wr_param *param)
{
	struct ulptx_walk ulp_walk;
	struct chcr_ahash_req_ctx *reqctx = ahash_request_ctx(req);

	if (reqctx->hctx_wr.imm) {
		u8 *buf = (u8 *)ulptx;

		if (param->bfr_len) {
			memcpy(buf, reqctx->reqbfr, param->bfr_len);
			buf += param->bfr_len;
		}

		sg_pcopy_to_buffer(reqctx->hctx_wr.srcsg,
				   sg_nents(reqctx->hctx_wr.srcsg), buf,
				   param->sg_len, 0);
	} else {
		ulptx_walk_init(&ulp_walk, ulptx);
		if (param->bfr_len)
			ulptx_walk_add_page(&ulp_walk, param->bfr_len,
					    reqctx->hctx_wr.dma_addr);
		ulptx_walk_add_sg(&ulp_walk, reqctx->hctx_wr.srcsg,
				  param->sg_len, reqctx->hctx_wr.src_ofst);
		reqctx->hctx_wr.srcsg = ulp_walk.last_sg;
		reqctx->hctx_wr.src_ofst = ulp_walk.last_sg_len;
		ulptx_walk_end(&ulp_walk);
	}
}