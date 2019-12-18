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
struct safexcel_ahash_req {int /*<<< orphan*/  cache; int /*<<< orphan*/  state_sz; int /*<<< orphan*/  state; int /*<<< orphan*/  digest; int /*<<< orphan*/  processed; int /*<<< orphan*/  len; } ;
struct safexcel_ahash_export_state {int /*<<< orphan*/  cache; int /*<<< orphan*/  state; int /*<<< orphan*/  digest; int /*<<< orphan*/  processed; int /*<<< orphan*/  len; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_CACHE_SIZE ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int safexcel_ahash_export(struct ahash_request *areq, void *out)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_ahash_export_state *export = out;

	export->len = req->len;
	export->processed = req->processed;

	export->digest = req->digest;

	memcpy(export->state, req->state, req->state_sz);
	memcpy(export->cache, req->cache, HASH_CACHE_SIZE);

	return 0;
}