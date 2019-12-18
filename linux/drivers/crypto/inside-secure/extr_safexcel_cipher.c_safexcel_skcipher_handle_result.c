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
struct skcipher_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct safexcel_crypto_priv {int dummy; } ;
struct safexcel_cipher_req {int needs_inv; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 int safexcel_handle_inv_result (struct safexcel_crypto_priv*,int,struct crypto_async_request*,struct safexcel_cipher_req*,int*,int*) ; 
 int safexcel_handle_req_result (struct safexcel_crypto_priv*,int,struct crypto_async_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_cipher_req*,int*,int*) ; 
 struct skcipher_request* skcipher_request_cast (struct crypto_async_request*) ; 
 struct safexcel_cipher_req* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int safexcel_skcipher_handle_result(struct safexcel_crypto_priv *priv,
					   int ring,
					   struct crypto_async_request *async,
					   bool *should_complete, int *ret)
{
	struct skcipher_request *req = skcipher_request_cast(async);
	struct safexcel_cipher_req *sreq = skcipher_request_ctx(req);
	int err;

	if (sreq->needs_inv) {
		sreq->needs_inv = false;
		err = safexcel_handle_inv_result(priv, ring, async, sreq,
						 should_complete, ret);
	} else {
		err = safexcel_handle_req_result(priv, ring, async, req->src,
						 req->dst, req->cryptlen, sreq,
						 should_complete, ret);
	}

	return err;
}