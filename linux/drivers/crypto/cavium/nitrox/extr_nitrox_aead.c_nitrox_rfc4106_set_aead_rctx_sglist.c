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
struct scatterlist {int dummy; } ;
struct nitrox_aead_rctx {struct scatterlist* dst; struct scatterlist* src; } ;
struct nitrox_rfc4106_rctx {struct scatterlist* dst; struct scatterlist* src; int /*<<< orphan*/  assoc; struct nitrox_aead_rctx base; } ;
struct aead_request {unsigned int assoclen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GCM_RFC4106_IV_SIZE ; 
 struct nitrox_rfc4106_rctx* aead_request_ctx (struct aead_request*) ; 
 struct scatterlist* scatterwalk_ffwd (struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_chain (struct scatterlist*,int,struct scatterlist*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int nitrox_rfc4106_set_aead_rctx_sglist(struct aead_request *areq)
{
	struct nitrox_rfc4106_rctx *rctx = aead_request_ctx(areq);
	struct nitrox_aead_rctx *aead_rctx = &rctx->base;
	unsigned int assoclen = areq->assoclen - GCM_RFC4106_IV_SIZE;
	struct scatterlist *sg;

	if (areq->assoclen != 16 && areq->assoclen != 20)
		return -EINVAL;

	scatterwalk_map_and_copy(rctx->assoc, areq->src, 0, assoclen, 0);
	sg_init_table(rctx->src, 3);
	sg_set_buf(rctx->src, rctx->assoc, assoclen);
	sg = scatterwalk_ffwd(rctx->src + 1, areq->src, areq->assoclen);
	if (sg != rctx->src + 1)
		sg_chain(rctx->src, 2, sg);

	if (areq->src != areq->dst) {
		sg_init_table(rctx->dst, 3);
		sg_set_buf(rctx->dst, rctx->assoc, assoclen);
		sg = scatterwalk_ffwd(rctx->dst + 1, areq->dst, areq->assoclen);
		if (sg != rctx->dst + 1)
			sg_chain(rctx->dst, 2, sg);
	}

	aead_rctx->src = rctx->src;
	aead_rctx->dst = (areq->src == areq->dst) ? rctx->src : rctx->dst;

	return 0;
}