#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_tfm {TYPE_2__* __crt_alg; } ;
struct crypto_async_request {struct crypto_tfm* tfm; } ;
struct chcr_context {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  complete; } ;
struct adapter {TYPE_1__ chcr_stats; } ;
struct TYPE_4__ {int cra_flags; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_ABLKCIPHER 130 
#define  CRYPTO_ALG_TYPE_AEAD 129 
#define  CRYPTO_ALG_TYPE_AHASH 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  ablkcipher_request_cast (struct crypto_async_request*) ; 
 int /*<<< orphan*/  aead_request_cast (struct crypto_async_request*) ; 
 int /*<<< orphan*/  ahash_request_cast (struct crypto_async_request*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int chcr_handle_aead_resp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  chcr_handle_ahash_resp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  chcr_handle_cipher_resp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 struct chcr_context* crypto_tfm_ctx (struct crypto_tfm*) ; 
 struct adapter* padap (int /*<<< orphan*/ ) ; 

int chcr_handle_resp(struct crypto_async_request *req, unsigned char *input,
			 int err)
{
	struct crypto_tfm *tfm = req->tfm;
	struct chcr_context *ctx = crypto_tfm_ctx(tfm);
	struct adapter *adap = padap(ctx->dev);

	switch (tfm->__crt_alg->cra_flags & CRYPTO_ALG_TYPE_MASK) {
	case CRYPTO_ALG_TYPE_AEAD:
		err = chcr_handle_aead_resp(aead_request_cast(req), input, err);
		break;

	case CRYPTO_ALG_TYPE_ABLKCIPHER:
		 chcr_handle_cipher_resp(ablkcipher_request_cast(req),
					       input, err);
		break;
	case CRYPTO_ALG_TYPE_AHASH:
		chcr_handle_ahash_resp(ahash_request_cast(req), input, err);
		}
	atomic_inc(&adap->chcr_stats.complete);
	return err;
}