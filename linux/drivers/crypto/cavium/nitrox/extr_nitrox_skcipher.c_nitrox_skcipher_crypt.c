#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
struct skcipher_request {int cryptlen; TYPE_1__ base; } ;
struct TYPE_9__ {int ctxl; int /*<<< orphan*/  arg; } ;
struct TYPE_10__ {TYPE_4__ s; scalar_t__ value; } ;
struct TYPE_7__ {scalar_t__ param3; void* param2; scalar_t__ param1; void* param0; } ;
struct se_crypto_request {int flags; TYPE_5__ ctrl; int /*<<< orphan*/  ctx_handle; TYPE_2__ gph; int /*<<< orphan*/  opcode; int /*<<< orphan*/  gfp; } ;
struct nitrox_kcrypt_request {struct se_crypto_request creq; } ;
struct TYPE_8__ {int /*<<< orphan*/  ctx_handle; } ;
struct nitrox_crypto_ctx {int /*<<< orphan*/  ndev; TYPE_3__ u; } ;
struct flexi_crypto_context {int dummy; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DECRYPT ; 
 int /*<<< orphan*/  ENCRYPT ; 
 int /*<<< orphan*/  FLEXI_CRYPTO_ENCRYPT_HMAC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int alloc_dst_sglist (struct skcipher_request*,int) ; 
 int alloc_src_sglist (struct skcipher_request*,int) ; 
 void* cpu_to_be16 (int) ; 
 struct nitrox_crypto_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  free_src_sglist (struct skcipher_request*) ; 
 int nitrox_process_se_request (int /*<<< orphan*/ ,struct se_crypto_request*,int /*<<< orphan*/ ,struct skcipher_request*) ; 
 int /*<<< orphan*/  nitrox_skcipher_callback ; 
 struct nitrox_kcrypt_request* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int nitrox_skcipher_crypt(struct skcipher_request *skreq, bool enc)
{
	struct crypto_skcipher *cipher = crypto_skcipher_reqtfm(skreq);
	struct nitrox_crypto_ctx *nctx = crypto_skcipher_ctx(cipher);
	struct nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);
	int ivsize = crypto_skcipher_ivsize(cipher);
	struct se_crypto_request *creq;
	int ret;

	creq = &nkreq->creq;
	creq->flags = skreq->base.flags;
	creq->gfp = (skreq->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		     GFP_KERNEL : GFP_ATOMIC;

	/* fill the request */
	creq->ctrl.value = 0;
	creq->opcode = FLEXI_CRYPTO_ENCRYPT_HMAC;
	creq->ctrl.s.arg = (enc ? ENCRYPT : DECRYPT);
	/* param0: length of the data to be encrypted */
	creq->gph.param0 = cpu_to_be16(skreq->cryptlen);
	creq->gph.param1 = 0;
	/* param2: encryption data offset */
	creq->gph.param2 = cpu_to_be16(ivsize);
	creq->gph.param3 = 0;

	creq->ctx_handle = nctx->u.ctx_handle;
	creq->ctrl.s.ctxl = sizeof(struct flexi_crypto_context);

	ret = alloc_src_sglist(skreq, ivsize);
	if (ret)
		return ret;

	ret = alloc_dst_sglist(skreq, ivsize);
	if (ret) {
		free_src_sglist(skreq);
		return ret;
	}

	/* send the crypto request */
	return nitrox_process_se_request(nctx->ndev, creq,
					 nitrox_skcipher_callback, skreq);
}