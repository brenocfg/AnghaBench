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
struct omap_des_reqctx {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  do_one_request; int /*<<< orphan*/ * unprepare_request; int /*<<< orphan*/  prepare_request; } ;
struct TYPE_6__ {TYPE_2__ op; } ;
struct omap_des_ctx {TYPE_3__ enginectx; } ;
struct TYPE_4__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;

/* Variables and functions */
 struct omap_des_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  omap_des_crypt_req ; 
 int /*<<< orphan*/  omap_des_prepare_req ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int omap_des_cra_init(struct crypto_tfm *tfm)
{
	struct omap_des_ctx *ctx = crypto_tfm_ctx(tfm);

	pr_debug("enter\n");

	tfm->crt_ablkcipher.reqsize = sizeof(struct omap_des_reqctx);

	ctx->enginectx.op.prepare_request = omap_des_prepare_req;
	ctx->enginectx.op.unprepare_request = NULL;
	ctx->enginectx.op.do_one_request = omap_des_crypt_req;

	return 0;
}