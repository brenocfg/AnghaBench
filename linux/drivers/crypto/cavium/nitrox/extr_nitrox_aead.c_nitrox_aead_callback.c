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
struct nitrox_aead_rctx {int /*<<< orphan*/  nkreq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct aead_request {TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nitrox_aead_rctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  free_dst_sglist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_src_sglist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static void nitrox_aead_callback(void *arg, int err)
{
	struct aead_request *areq = arg;
	struct nitrox_aead_rctx *rctx = aead_request_ctx(areq);

	free_src_sglist(&rctx->nkreq);
	free_dst_sglist(&rctx->nkreq);
	if (err) {
		pr_err_ratelimited("request failed status 0x%0x\n", err);
		err = -EINVAL;
	}

	areq->base.complete(&areq->base, err);
}