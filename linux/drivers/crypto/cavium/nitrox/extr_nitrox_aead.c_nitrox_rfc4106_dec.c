#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct se_crypto_request {int dummy; } ;
struct TYPE_4__ {struct se_crypto_request creq; } ;
struct nitrox_aead_rctx {void* cryptlen; void* srclen; void* dstlen; int /*<<< orphan*/  ctrl_arg; int /*<<< orphan*/  ctx_handle; int /*<<< orphan*/  flags; void* ivsize; int /*<<< orphan*/  iv; void* assoclen; TYPE_1__ nkreq; } ;
struct nitrox_rfc4106_rctx {struct nitrox_aead_rctx base; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx_handle; } ;
struct nitrox_crypto_ctx {int /*<<< orphan*/  ndev; TYPE_3__ u; } ;
struct crypto_aead {void* authsize; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct aead_request {void* cryptlen; void* assoclen; TYPE_2__ base; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECRYPT ; 
 void* GCM_RFC4106_IV_SIZE ; 
 struct nitrox_rfc4106_rctx* aead_request_ctx (struct aead_request*) ; 
 struct nitrox_crypto_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int nitrox_process_se_request (int /*<<< orphan*/ ,struct se_crypto_request*,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  nitrox_rfc4106_callback ; 
 int nitrox_rfc4106_set_aead_rctx_sglist (struct aead_request*) ; 
 int nitrox_set_creq (struct nitrox_aead_rctx*) ; 

__attribute__((used)) static int nitrox_rfc4106_dec(struct aead_request *areq)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(areq);
	struct nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	struct nitrox_rfc4106_rctx *rctx = aead_request_ctx(areq);
	struct nitrox_aead_rctx *aead_rctx = &rctx->base;
	struct se_crypto_request *creq = &aead_rctx->nkreq.creq;
	int ret;

	aead_rctx->cryptlen = areq->cryptlen - aead->authsize;
	aead_rctx->assoclen = areq->assoclen - GCM_RFC4106_IV_SIZE;
	aead_rctx->srclen =
		areq->cryptlen - GCM_RFC4106_IV_SIZE + areq->assoclen;
	aead_rctx->dstlen = aead_rctx->srclen - aead->authsize;
	aead_rctx->iv = areq->iv;
	aead_rctx->ivsize = GCM_RFC4106_IV_SIZE;
	aead_rctx->flags = areq->base.flags;
	aead_rctx->ctx_handle = nctx->u.ctx_handle;
	aead_rctx->ctrl_arg = DECRYPT;

	ret = nitrox_rfc4106_set_aead_rctx_sglist(areq);
	if (ret)
		return ret;

	ret = nitrox_set_creq(aead_rctx);
	if (ret)
		return ret;

	/* send the crypto request */
	return nitrox_process_se_request(nctx->ndev, creq,
					 nitrox_rfc4106_callback, areq);
}