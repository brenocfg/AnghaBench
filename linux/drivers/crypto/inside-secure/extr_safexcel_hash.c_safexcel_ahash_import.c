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
struct safexcel_ahash_req {int /*<<< orphan*/  state_sz; int /*<<< orphan*/  state; int /*<<< orphan*/  cache; int /*<<< orphan*/  digest; int /*<<< orphan*/  processed; int /*<<< orphan*/  len; } ;
struct safexcel_ahash_export_state {int /*<<< orphan*/  state; int /*<<< orphan*/  cache; int /*<<< orphan*/  digest; int /*<<< orphan*/  processed; int /*<<< orphan*/  len; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_CACHE_SIZE ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int crypto_ahash_init (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int safexcel_ahash_import(struct ahash_request *areq, const void *in)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	const struct safexcel_ahash_export_state *export = in;
	int ret;

	ret = crypto_ahash_init(areq);
	if (ret)
		return ret;

	req->len = export->len;
	req->processed = export->processed;

	req->digest = export->digest;

	memcpy(req->cache, export->cache, HASH_CACHE_SIZE);
	memcpy(req->state, export->state, req->state_sz);

	return 0;
}