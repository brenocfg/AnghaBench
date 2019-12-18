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
struct mv_cesa_engine {int dummy; } ;
struct mv_cesa_ahash_req {int /*<<< orphan*/  base; } ;
struct ahash_request {int /*<<< orphan*/  base; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  mv_cesa_ahash_cleanup (struct ahash_request*) ; 
 int /*<<< orphan*/  mv_cesa_ahash_prepare (int /*<<< orphan*/ *,struct mv_cesa_engine*) ; 
 int mv_cesa_ahash_req_init (struct ahash_request*,int*) ; 
 int mv_cesa_queue_req (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mv_cesa_req_needs_cleanup (int /*<<< orphan*/ *,int) ; 
 struct mv_cesa_engine* mv_cesa_select_engine (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_cesa_ahash_queue_req(struct ahash_request *req)
{
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	struct mv_cesa_engine *engine;
	bool cached = false;
	int ret;

	ret = mv_cesa_ahash_req_init(req, &cached);
	if (ret)
		return ret;

	if (cached)
		return 0;

	engine = mv_cesa_select_engine(req->nbytes);
	mv_cesa_ahash_prepare(&req->base, engine);

	ret = mv_cesa_queue_req(&req->base, &creq->base);

	if (mv_cesa_req_needs_cleanup(&req->base, ret))
		mv_cesa_ahash_cleanup(req);

	return ret;
}