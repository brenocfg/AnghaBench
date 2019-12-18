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
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; struct crypto_alg* __crt_alg; } ;
struct crypto_alg {int /*<<< orphan*/  cra_name; } ;
struct chcr_context {int dummy; } ;
struct chcr_blkcipher_req_ctx {int dummy; } ;
struct ablk_ctx {int /*<<< orphan*/  sw_cipher; } ;

/* Variables and functions */
 struct ablk_ctx* ABLK_CTX (struct chcr_context*) ; 
 int /*<<< orphan*/  CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int chcr_device_init (struct chcr_context*) ; 
 int /*<<< orphan*/  crypto_alloc_sync_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct chcr_context* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chcr_rfc3686_init(struct crypto_tfm *tfm)
{
	struct crypto_alg *alg = tfm->__crt_alg;
	struct chcr_context *ctx = crypto_tfm_ctx(tfm);
	struct ablk_ctx *ablkctx = ABLK_CTX(ctx);

	/*RFC3686 initialises IV counter value to 1, rfc3686(ctr(aes))
	 * cannot be used as fallback in chcr_handle_cipher_response
	 */
	ablkctx->sw_cipher = crypto_alloc_sync_skcipher("ctr(aes)", 0,
				CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(ablkctx->sw_cipher)) {
		pr_err("failed to allocate fallback for %s\n", alg->cra_name);
		return PTR_ERR(ablkctx->sw_cipher);
	}
	tfm->crt_ablkcipher.reqsize =  sizeof(struct chcr_blkcipher_req_ctx);
	return chcr_device_init(crypto_tfm_ctx(tfm));
}