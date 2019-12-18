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
struct crypto_tfm {int dummy; } ;
struct crypto_shash {int dummy; } ;
struct TYPE_3__ {struct crypto_shash* hmac_tfm; } ;
struct TYPE_4__ {TYPE_1__ sha; } ;
struct ccp_ctx {TYPE_2__ u; } ;
struct ccp_crypto_ahash_alg {int /*<<< orphan*/  child_alg; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 struct ccp_crypto_ahash_alg* ccp_crypto_ahash_alg (struct crypto_tfm*) ; 
 int ccp_sha_cra_init (struct crypto_tfm*) ; 
 struct crypto_shash* crypto_alloc_shash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ccp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccp_hmac_sha_cra_init(struct crypto_tfm *tfm)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(tfm);
	struct ccp_crypto_ahash_alg *alg = ccp_crypto_ahash_alg(tfm);
	struct crypto_shash *hmac_tfm;

	hmac_tfm = crypto_alloc_shash(alg->child_alg, 0, 0);
	if (IS_ERR(hmac_tfm)) {
		pr_warn("could not load driver %s need for HMAC support\n",
			alg->child_alg);
		return PTR_ERR(hmac_tfm);
	}

	ctx->u.sha.hmac_tfm = hmac_tfm;

	return ccp_sha_cra_init(tfm);
}