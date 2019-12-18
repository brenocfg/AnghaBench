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
typedef  unsigned int u64 ;
struct mv_cesa_ahash_req {unsigned int len; unsigned int cache_ptr; int /*<<< orphan*/  cache; int /*<<< orphan*/  state; int /*<<< orphan*/  op_tmpl; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_SA_DESC_CFG_FRAG_MSK ; 
 int /*<<< orphan*/  CESA_SA_DESC_CFG_MID_FRAG ; 
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 unsigned int crypto_ahash_blocksize (struct crypto_ahash*) ; 
 unsigned int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int crypto_ahash_init (struct ahash_request*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 unsigned int do_div (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,unsigned int) ; 
 int /*<<< orphan*/  mv_cesa_update_op_cfg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_cesa_ahash_import(struct ahash_request *req, const void *hash,
				u64 len, const void *cache)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	unsigned int digsize = crypto_ahash_digestsize(ahash);
	unsigned int blocksize;
	unsigned int cache_ptr;
	int ret;

	ret = crypto_ahash_init(req);
	if (ret)
		return ret;

	blocksize = crypto_ahash_blocksize(ahash);
	if (len >= blocksize)
		mv_cesa_update_op_cfg(&creq->op_tmpl,
				      CESA_SA_DESC_CFG_MID_FRAG,
				      CESA_SA_DESC_CFG_FRAG_MSK);

	creq->len = len;
	memcpy(creq->state, hash, digsize);
	creq->cache_ptr = 0;

	cache_ptr = do_div(len, blocksize);
	if (!cache_ptr)
		return 0;

	memcpy(creq->cache, cache, cache_ptr);
	creq->cache_ptr = cache_ptr;

	return 0;
}