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
struct dcp_async_ctx {scalar_t__ key_len; size_t chan; } ;
struct dcp_aes_req_ctx {int enc; int ecb; } ;
struct dcp {int /*<<< orphan*/ * thread; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * queue; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {struct crypto_async_request base; } ;

/* Variables and functions */
 scalar_t__ AES_KEYSIZE_128 ; 
 size_t DCP_CHAN_CRYPTO ; 
 struct dcp_aes_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 struct dcp_async_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 struct dcp* global_sdcp ; 
 int mxs_dcp_block_fallback (struct ablkcipher_request*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxs_dcp_aes_enqueue(struct ablkcipher_request *req, int enc, int ecb)
{
	struct dcp *sdcp = global_sdcp;
	struct crypto_async_request *arq = &req->base;
	struct dcp_async_ctx *actx = crypto_tfm_ctx(arq->tfm);
	struct dcp_aes_req_ctx *rctx = ablkcipher_request_ctx(req);
	int ret;

	if (unlikely(actx->key_len != AES_KEYSIZE_128))
		return mxs_dcp_block_fallback(req, enc);

	rctx->enc = enc;
	rctx->ecb = ecb;
	actx->chan = DCP_CHAN_CRYPTO;

	spin_lock(&sdcp->lock[actx->chan]);
	ret = crypto_enqueue_request(&sdcp->queue[actx->chan], &req->base);
	spin_unlock(&sdcp->lock[actx->chan]);

	wake_up_process(sdcp->thread[actx->chan]);

	return ret;
}