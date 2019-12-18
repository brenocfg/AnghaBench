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
struct TYPE_4__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct crypto_sync_skcipher {int dummy; } ;
struct TYPE_5__ {struct crypto_sync_skcipher* tfm_skcipher; scalar_t__ key_len; } ;
struct TYPE_6__ {TYPE_2__ aes; } ;
struct ccp_ctx {TYPE_3__ u; int /*<<< orphan*/  complete; } ;
struct ccp_aes_req_ctx {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (struct crypto_sync_skcipher*) ; 
 int PTR_ERR (struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  ccp_aes_xts_complete ; 
 struct crypto_sync_skcipher* crypto_alloc_sync_skcipher (char*,int /*<<< orphan*/ ,int) ; 
 struct ccp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int ccp_aes_xts_cra_init(struct crypto_tfm *tfm)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_sync_skcipher *fallback_tfm;

	ctx->complete = ccp_aes_xts_complete;
	ctx->u.aes.key_len = 0;

	fallback_tfm = crypto_alloc_sync_skcipher("xts(aes)", 0,
					     CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(fallback_tfm)) {
		pr_warn("could not load fallback driver xts(aes)\n");
		return PTR_ERR(fallback_tfm);
	}
	ctx->u.aes.tfm_skcipher = fallback_tfm;

	tfm->crt_ablkcipher.reqsize = sizeof(struct ccp_aes_req_ctx);

	return 0;
}