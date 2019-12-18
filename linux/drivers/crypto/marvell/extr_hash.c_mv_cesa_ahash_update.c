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
struct mv_cesa_ahash_req {int /*<<< orphan*/  len; } ;
struct ahash_request {scalar_t__ nbytes; } ;

/* Variables and functions */
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int mv_cesa_ahash_queue_req (struct ahash_request*) ; 

__attribute__((used)) static int mv_cesa_ahash_update(struct ahash_request *req)
{
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);

	creq->len += req->nbytes;

	return mv_cesa_ahash_queue_req(req);
}