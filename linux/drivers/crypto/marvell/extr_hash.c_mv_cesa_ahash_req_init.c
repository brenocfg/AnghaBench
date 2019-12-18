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
struct mv_cesa_ahash_req {scalar_t__ src_nents; } ;
struct ahash_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; } ;
struct TYPE_4__ {TYPE_1__* caps; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ has_tdma; } ;

/* Variables and functions */
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 TYPE_2__* cesa_dev ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mv_cesa_ahash_cache_req (struct ahash_request*) ; 
 int mv_cesa_ahash_dma_req_init (struct ahash_request*) ; 
 scalar_t__ sg_nents_for_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_cesa_ahash_req_init(struct ahash_request *req, bool *cached)
{
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	creq->src_nents = sg_nents_for_len(req->src, req->nbytes);
	if (creq->src_nents < 0) {
		dev_err(cesa_dev->dev, "Invalid number of src SG");
		return creq->src_nents;
	}

	*cached = mv_cesa_ahash_cache_req(req);

	if (*cached)
		return 0;

	if (cesa_dev->caps->has_tdma)
		return mv_cesa_ahash_dma_req_init(req);
	else
		return 0;
}