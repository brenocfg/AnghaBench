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
typedef  int /*<<< orphan*/  u8 ;
struct ulptx_walk {int /*<<< orphan*/  last_sg_len; int /*<<< orphan*/  last_sg; } ;
struct ulptx_sgl {int dummy; } ;
struct cipher_wr_param {int /*<<< orphan*/  bytes; } ;
struct chcr_blkcipher_req_ctx {int /*<<< orphan*/  src_ofst; int /*<<< orphan*/  srcsg; int /*<<< orphan*/  processed; scalar_t__ imm; int /*<<< orphan*/  iv; } ;
struct ablkcipher_request {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  IV ; 
 struct chcr_blkcipher_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulptx_walk_add_sg (struct ulptx_walk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulptx_walk_end (struct ulptx_walk*) ; 
 int /*<<< orphan*/  ulptx_walk_init (struct ulptx_walk*,struct ulptx_sgl*) ; 

void chcr_add_cipher_src_ent(struct ablkcipher_request *req,
			     void *ulptx,
			     struct  cipher_wr_param *wrparam)
{
	struct ulptx_walk ulp_walk;
	struct chcr_blkcipher_req_ctx *reqctx = ablkcipher_request_ctx(req);
	u8 *buf = ulptx;

	memcpy(buf, reqctx->iv, IV);
	buf += IV;
	if (reqctx->imm) {
		sg_pcopy_to_buffer(req->src, sg_nents(req->src),
				   buf, wrparam->bytes, reqctx->processed);
	} else {
		ulptx_walk_init(&ulp_walk, (struct ulptx_sgl *)buf);
		ulptx_walk_add_sg(&ulp_walk, reqctx->srcsg, wrparam->bytes,
				  reqctx->src_ofst);
		reqctx->srcsg = ulp_walk.last_sg;
		reqctx->src_ofst = ulp_walk.last_sg_len;
		ulptx_walk_end(&ulp_walk);
	}
}