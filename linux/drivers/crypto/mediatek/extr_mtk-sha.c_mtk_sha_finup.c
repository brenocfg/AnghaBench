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
struct mtk_sha_reqctx {int /*<<< orphan*/  flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  SHA_FLAGS_FINUP ; 
 struct mtk_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int ahash_request_flags (struct ahash_request*) ; 
 int mtk_sha_final (struct ahash_request*) ; 
 int mtk_sha_update (struct ahash_request*) ; 

__attribute__((used)) static int mtk_sha_finup(struct ahash_request *req)
{
	struct mtk_sha_reqctx *ctx = ahash_request_ctx(req);
	int err1, err2;

	ctx->flags |= SHA_FLAGS_FINUP;

	err1 = mtk_sha_update(req);
	if (err1 == -EINPROGRESS ||
	    (err1 == -EBUSY && (ahash_request_flags(req) &
				CRYPTO_TFM_REQ_MAY_BACKLOG)))
		return err1;
	/*
	 * final() has to be always called to cleanup resources
	 * even if update() failed
	 */
	err2 = mtk_sha_final(req);

	return err1 ?: err2;
}