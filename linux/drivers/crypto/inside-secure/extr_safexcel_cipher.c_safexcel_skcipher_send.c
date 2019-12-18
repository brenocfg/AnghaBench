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
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct skcipher_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; TYPE_1__ base; } ;
struct safexcel_crypto_priv {int flags; } ;
struct safexcel_cipher_req {int rdescs; scalar_t__ needs_inv; } ;
struct safexcel_cipher_ctx {struct safexcel_crypto_priv* priv; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIP197_TRC_CACHE ; 
 int /*<<< orphan*/  crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int safexcel_cipher_send_inv (struct crypto_async_request*,int,int*,int*) ; 
 int safexcel_send_req (struct crypto_async_request*,int,struct safexcel_cipher_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 struct skcipher_request* skcipher_request_cast (struct crypto_async_request*) ; 
 struct safexcel_cipher_req* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int safexcel_skcipher_send(struct crypto_async_request *async, int ring,
				  int *commands, int *results)
{
	struct skcipher_request *req = skcipher_request_cast(async);
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	struct safexcel_cipher_req *sreq = skcipher_request_ctx(req);
	struct safexcel_crypto_priv *priv = ctx->priv;
	int ret;

	BUG_ON(!(priv->flags & EIP197_TRC_CACHE) && sreq->needs_inv);

	if (sreq->needs_inv) {
		ret = safexcel_cipher_send_inv(async, ring, commands, results);
	} else {
		struct crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
		u8 input_iv[AES_BLOCK_SIZE];

		/*
		 * Save input IV in case of CBC decrypt mode
		 * Will be overwritten with output IV prior to use!
		 */
		memcpy(input_iv, req->iv, crypto_skcipher_ivsize(skcipher));

		ret = safexcel_send_req(async, ring, sreq, req->src,
					req->dst, req->cryptlen, 0, 0, input_iv,
					commands, results);
	}

	sreq->rdescs = *results;
	return ret;
}