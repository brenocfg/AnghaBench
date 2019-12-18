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
struct stm32_cryp_reqctx {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * unprepare_request; int /*<<< orphan*/  prepare_request; int /*<<< orphan*/  do_one_request; } ;
struct TYPE_6__ {TYPE_2__ op; } ;
struct stm32_cryp_ctx {TYPE_3__ enginectx; } ;
struct TYPE_4__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;

/* Variables and functions */
 struct stm32_cryp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  stm32_cryp_cipher_one_req ; 
 int /*<<< orphan*/  stm32_cryp_prepare_cipher_req ; 

__attribute__((used)) static int stm32_cryp_cra_init(struct crypto_tfm *tfm)
{
	struct stm32_cryp_ctx *ctx = crypto_tfm_ctx(tfm);

	tfm->crt_ablkcipher.reqsize = sizeof(struct stm32_cryp_reqctx);

	ctx->enginectx.op.do_one_request = stm32_cryp_cipher_one_req;
	ctx->enginectx.op.prepare_request = stm32_cryp_prepare_cipher_req;
	ctx->enginectx.op.unprepare_request = NULL;
	return 0;
}