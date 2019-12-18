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
struct mtk_sha_reqctx {int flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int SHA_FLAGS_FINUP ; 
 int SHA_FLAGS_PAD ; 
 int /*<<< orphan*/  SHA_OP_FINAL ; 
 struct mtk_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int mtk_sha_enqueue (struct ahash_request*,int /*<<< orphan*/ ) ; 
 int mtk_sha_finish (struct ahash_request*) ; 

__attribute__((used)) static int mtk_sha_final(struct ahash_request *req)
{
	struct mtk_sha_reqctx *ctx = ahash_request_ctx(req);

	ctx->flags |= SHA_FLAGS_FINUP;

	if (ctx->flags & SHA_FLAGS_PAD)
		return mtk_sha_finish(req);

	return mtk_sha_enqueue(req, SHA_OP_FINAL);
}