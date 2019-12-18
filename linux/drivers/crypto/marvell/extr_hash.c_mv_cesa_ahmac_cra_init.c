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
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct mv_cesa_hmac_ctx {TYPE_1__ base; } ;
struct mv_cesa_ahash_req {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,int) ; 
 struct mv_cesa_hmac_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  mv_cesa_ahash_req_ops ; 

__attribute__((used)) static int mv_cesa_ahmac_cra_init(struct crypto_tfm *tfm)
{
	struct mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->base.ops = &mv_cesa_ahash_req_ops;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct mv_cesa_ahash_req));
	return 0;
}