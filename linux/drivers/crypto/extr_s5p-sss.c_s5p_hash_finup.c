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
struct s5p_hash_reqctx {int finup; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int s5p_hash_final (struct ahash_request*) ; 
 int s5p_hash_update (struct ahash_request*) ; 

__attribute__((used)) static int s5p_hash_finup(struct ahash_request *req)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	int err1, err2;

	ctx->finup = true;

	err1 = s5p_hash_update(req);
	if (err1 == -EINPROGRESS || err1 == -EBUSY)
		return err1;

	/*
	 * final() has to be always called to cleanup resources even if
	 * update() failed, except EINPROGRESS or calculate digest for small
	 * size
	 */
	err2 = s5p_hash_final(req);

	return err1 ?: err2;
}