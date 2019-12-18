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
struct mtk_cryp {int dummy; } ;
struct mtk_aes_reqctx {int dummy; } ;
struct mtk_aes_rec {int /*<<< orphan*/  resume; int /*<<< orphan*/  areq; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 struct mtk_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int mtk_aes_dma (struct mtk_cryp*,struct mtk_aes_rec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_aes_set_mode (struct mtk_aes_rec*,struct mtk_aes_reqctx*) ; 
 int /*<<< orphan*/  mtk_aes_transfer_complete ; 

__attribute__((used)) static int mtk_aes_start(struct mtk_cryp *cryp, struct mtk_aes_rec *aes)
{
	struct ablkcipher_request *req = ablkcipher_request_cast(aes->areq);
	struct mtk_aes_reqctx *rctx = ablkcipher_request_ctx(req);

	mtk_aes_set_mode(aes, rctx);
	aes->resume = mtk_aes_transfer_complete;

	return mtk_aes_dma(cryp, aes, req->src, req->dst, req->nbytes);
}