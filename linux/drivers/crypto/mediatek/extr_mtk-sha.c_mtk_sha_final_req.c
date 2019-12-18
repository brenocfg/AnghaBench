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
struct mtk_sha_reqctx {size_t bufcnt; } ;
struct mtk_sha_rec {int /*<<< orphan*/  flags; int /*<<< orphan*/  req; } ;
struct mtk_cryp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_FLAGS_FINAL ; 
 struct mtk_sha_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int mtk_sha_dma_map (struct mtk_cryp*,struct mtk_sha_rec*,struct mtk_sha_reqctx*,size_t) ; 
 int /*<<< orphan*/  mtk_sha_fill_padding (struct mtk_sha_reqctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_sha_final_req(struct mtk_cryp *cryp,
			     struct mtk_sha_rec *sha)
{
	struct mtk_sha_reqctx *ctx = ahash_request_ctx(sha->req);
	size_t count;

	mtk_sha_fill_padding(ctx, 0);

	sha->flags |= SHA_FLAGS_FINAL;
	count = ctx->bufcnt;
	ctx->bufcnt = 0;

	return mtk_sha_dma_map(cryp, sha, ctx, count);
}