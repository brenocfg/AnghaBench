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
struct safexcel_ahash_req {scalar_t__ last_req; int /*<<< orphan*/  finish; int /*<<< orphan*/  len; } ;
struct ahash_request {scalar_t__ nbytes; } ;

/* Variables and functions */
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int safexcel_ahash_cache (struct ahash_request*) ; 
 int safexcel_ahash_enqueue (struct ahash_request*) ; 

__attribute__((used)) static int safexcel_ahash_update(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	int ret;

	/* If the request is 0 length, do nothing */
	if (!areq->nbytes)
		return 0;

	/* Add request to the cache if it fits */
	ret = safexcel_ahash_cache(areq);

	/* Update total request length */
	req->len += areq->nbytes;

	/* If not all data could fit into the cache, go process the excess.
	 * Also go process immediately for an HMAC IV precompute, which
	 * will never be finished at all, but needs to be processed anyway.
	 */
	if ((ret && !req->finish) || req->last_req)
		return safexcel_ahash_enqueue(areq);

	return 0;
}