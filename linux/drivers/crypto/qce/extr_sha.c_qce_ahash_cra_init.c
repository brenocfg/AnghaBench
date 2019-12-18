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
struct qce_sha_reqctx {int dummy; } ;
struct qce_sha_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 struct crypto_ahash* __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (struct crypto_ahash*,int) ; 
 struct qce_sha_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memset (struct qce_sha_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qce_ahash_cra_init(struct crypto_tfm *tfm)
{
	struct crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	struct qce_sha_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_ahash_set_reqsize(ahash, sizeof(struct qce_sha_reqctx));
	memset(ctx, 0, sizeof(*ctx));
	return 0;
}