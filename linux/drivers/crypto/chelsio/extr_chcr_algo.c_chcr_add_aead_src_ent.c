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
struct ulptx_walk {int dummy; } ;
struct ulptx_sgl {int dummy; } ;
struct chcr_aead_reqctx {int /*<<< orphan*/  b0_dma; scalar_t__ b0_len; int /*<<< orphan*/  scratch_pad; scalar_t__ imm; } ;
struct aead_request {scalar_t__ assoclen; scalar_t__ cryptlen; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 struct chcr_aead_reqctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulptx_walk_add_page (struct ulptx_walk*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulptx_walk_add_sg (struct ulptx_walk*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulptx_walk_end (struct ulptx_walk*) ; 
 int /*<<< orphan*/  ulptx_walk_init (struct ulptx_walk*,struct ulptx_sgl*) ; 

void chcr_add_aead_src_ent(struct aead_request *req,
			   struct ulptx_sgl *ulptx)
{
	struct ulptx_walk ulp_walk;
	struct chcr_aead_reqctx  *reqctx = aead_request_ctx(req);

	if (reqctx->imm) {
		u8 *buf = (u8 *)ulptx;

		if (reqctx->b0_len) {
			memcpy(buf, reqctx->scratch_pad, reqctx->b0_len);
			buf += reqctx->b0_len;
		}
		sg_pcopy_to_buffer(req->src, sg_nents(req->src),
				   buf, req->cryptlen + req->assoclen, 0);
	} else {
		ulptx_walk_init(&ulp_walk, ulptx);
		if (reqctx->b0_len)
			ulptx_walk_add_page(&ulp_walk, reqctx->b0_len,
					    reqctx->b0_dma);
		ulptx_walk_add_sg(&ulp_walk, req->src, req->cryptlen +
				  req->assoclen,  0);
		ulptx_walk_end(&ulp_walk);
	}
}