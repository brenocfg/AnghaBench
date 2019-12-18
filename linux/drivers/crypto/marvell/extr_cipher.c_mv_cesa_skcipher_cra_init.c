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
struct mv_cesa_skcipher_req {int dummy; } ;
struct mv_cesa_ctx {int /*<<< orphan*/ * ops; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __crypto_skcipher_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_reqsize (int /*<<< orphan*/ ,int) ; 
 struct mv_cesa_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  mv_cesa_skcipher_req_ops ; 

__attribute__((used)) static int mv_cesa_skcipher_cra_init(struct crypto_tfm *tfm)
{
	struct mv_cesa_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->ops = &mv_cesa_skcipher_req_ops;

	crypto_skcipher_set_reqsize(__crypto_skcipher_cast(tfm),
				    sizeof(struct mv_cesa_skcipher_req));

	return 0;
}