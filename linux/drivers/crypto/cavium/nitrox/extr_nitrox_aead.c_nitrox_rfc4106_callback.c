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
struct nitrox_kcrypt_request {int dummy; } ;
struct TYPE_3__ {struct nitrox_kcrypt_request nkreq; } ;
struct nitrox_rfc4106_rctx {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* complete ) (TYPE_2__*,int) ;} ;
struct aead_request {TYPE_2__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nitrox_rfc4106_rctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  free_dst_sglist (struct nitrox_kcrypt_request*) ; 
 int /*<<< orphan*/  free_src_sglist (struct nitrox_kcrypt_request*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void nitrox_rfc4106_callback(void *arg, int err)
{
	struct aead_request *areq = arg;
	struct nitrox_rfc4106_rctx *rctx = aead_request_ctx(areq);
	struct nitrox_kcrypt_request *nkreq = &rctx->base.nkreq;

	free_src_sglist(nkreq);
	free_dst_sglist(nkreq);
	if (err) {
		pr_err_ratelimited("request failed status 0x%0x\n", err);
		err = -EINVAL;
	}

	areq->base.complete(&areq->base, err);
}