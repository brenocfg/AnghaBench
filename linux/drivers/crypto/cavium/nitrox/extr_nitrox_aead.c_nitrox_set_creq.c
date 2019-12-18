#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
union gph_p3 {scalar_t__ param; scalar_t__ auth_offset; scalar_t__ iv_offset; } ;
struct TYPE_8__ {int ctxl; int /*<<< orphan*/  arg; } ;
struct TYPE_9__ {TYPE_2__ s; scalar_t__ value; } ;
struct TYPE_7__ {void* param3; void* param2; void* param1; void* param0; } ;
struct se_crypto_request {int flags; TYPE_3__ ctrl; int /*<<< orphan*/  ctx_handle; TYPE_1__ gph; int /*<<< orphan*/  opcode; int /*<<< orphan*/  gfp; } ;
struct TYPE_10__ {struct se_crypto_request creq; } ;
struct nitrox_aead_rctx {int flags; TYPE_4__ nkreq; int /*<<< orphan*/  dstlen; scalar_t__ ivsize; int /*<<< orphan*/  dst; int /*<<< orphan*/  srclen; int /*<<< orphan*/  iv; int /*<<< orphan*/  src; int /*<<< orphan*/  ctx_handle; scalar_t__ assoclen; scalar_t__ cryptlen; int /*<<< orphan*/  ctrl_arg; } ;
struct flexi_crypto_context {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  FLEXI_CRYPTO_ENCRYPT_HMAC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int alloc_dst_sglist (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int alloc_src_sglist (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  free_src_sglist (TYPE_4__*) ; 

__attribute__((used)) static int nitrox_set_creq(struct nitrox_aead_rctx *rctx)
{
	struct se_crypto_request *creq = &rctx->nkreq.creq;
	union gph_p3 param3;
	int ret;

	creq->flags = rctx->flags;
	creq->gfp = (rctx->flags & CRYPTO_TFM_REQ_MAY_SLEEP) ? GFP_KERNEL :
							       GFP_ATOMIC;

	creq->ctrl.value = 0;
	creq->opcode = FLEXI_CRYPTO_ENCRYPT_HMAC;
	creq->ctrl.s.arg = rctx->ctrl_arg;

	creq->gph.param0 = cpu_to_be16(rctx->cryptlen);
	creq->gph.param1 = cpu_to_be16(rctx->cryptlen + rctx->assoclen);
	creq->gph.param2 = cpu_to_be16(rctx->ivsize + rctx->assoclen);
	param3.iv_offset = 0;
	param3.auth_offset = rctx->ivsize;
	creq->gph.param3 = cpu_to_be16(param3.param);

	creq->ctx_handle = rctx->ctx_handle;
	creq->ctrl.s.ctxl = sizeof(struct flexi_crypto_context);

	ret = alloc_src_sglist(&rctx->nkreq, rctx->src, rctx->iv, rctx->ivsize,
			       rctx->srclen);
	if (ret)
		return ret;

	ret = alloc_dst_sglist(&rctx->nkreq, rctx->dst, rctx->ivsize,
			       rctx->dstlen);
	if (ret) {
		free_src_sglist(&rctx->nkreq);
		return ret;
	}

	return 0;
}