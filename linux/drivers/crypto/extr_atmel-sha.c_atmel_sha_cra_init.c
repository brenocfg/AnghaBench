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
struct crypto_tfm {int dummy; } ;
struct atmel_sha_reqctx {int dummy; } ;
struct atmel_sha_ctx {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  atmel_sha_start ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (int /*<<< orphan*/ ,int) ; 
 struct atmel_sha_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int atmel_sha_cra_init(struct crypto_tfm *tfm)
{
	struct atmel_sha_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct atmel_sha_reqctx));
	ctx->start = atmel_sha_start;

	return 0;
}