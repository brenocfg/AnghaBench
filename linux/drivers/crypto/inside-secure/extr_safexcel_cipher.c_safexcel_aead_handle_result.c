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
struct safexcel_crypto_priv {int dummy; } ;
struct safexcel_cipher_req {int needs_inv; } ;
struct crypto_async_request {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {scalar_t__ cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 struct aead_request* aead_request_cast (struct crypto_async_request*) ; 
 struct safexcel_cipher_req* aead_request_ctx (struct aead_request*) ; 
 scalar_t__ crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int safexcel_handle_inv_result (struct safexcel_crypto_priv*,int,struct crypto_async_request*,struct safexcel_cipher_req*,int*,int*) ; 
 int safexcel_handle_req_result (struct safexcel_crypto_priv*,int,struct crypto_async_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct safexcel_cipher_req*,int*,int*) ; 

__attribute__((used)) static int safexcel_aead_handle_result(struct safexcel_crypto_priv *priv,
				       int ring,
				       struct crypto_async_request *async,
				       bool *should_complete, int *ret)
{
	struct aead_request *req = aead_request_cast(async);
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct safexcel_cipher_req *sreq = aead_request_ctx(req);
	int err;

	if (sreq->needs_inv) {
		sreq->needs_inv = false;
		err = safexcel_handle_inv_result(priv, ring, async, sreq,
						 should_complete, ret);
	} else {
		err = safexcel_handle_req_result(priv, ring, async, req->src,
						 req->dst,
						 req->cryptlen + crypto_aead_authsize(tfm),
						 sreq, should_complete, ret);
	}

	return err;
}