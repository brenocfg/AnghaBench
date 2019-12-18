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
struct dcp_async_ctx {struct crypto_sync_skcipher* fallback; } ;
struct dcp_aes_req_ctx {int dummy; } ;
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct crypto_sync_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (struct crypto_sync_skcipher*) ; 
 int PTR_ERR (struct crypto_sync_skcipher*) ; 
 struct crypto_sync_skcipher* crypto_alloc_sync_skcipher (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* crypto_tfm_alg_name (struct crypto_tfm*) ; 
 struct dcp_async_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int mxs_dcp_aes_fallback_init(struct crypto_tfm *tfm)
{
	const char *name = crypto_tfm_alg_name(tfm);
	struct dcp_async_ctx *actx = crypto_tfm_ctx(tfm);
	struct crypto_sync_skcipher *blk;

	blk = crypto_alloc_sync_skcipher(name, 0, CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(blk))
		return PTR_ERR(blk);

	actx->fallback = blk;
	tfm->crt_ablkcipher.reqsize = sizeof(struct dcp_aes_req_ctx);
	return 0;
}