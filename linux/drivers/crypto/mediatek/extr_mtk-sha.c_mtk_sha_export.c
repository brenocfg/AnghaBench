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
struct mtk_sha_reqctx {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct mtk_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (void*,struct mtk_sha_reqctx const*,int) ; 

__attribute__((used)) static int mtk_sha_export(struct ahash_request *req, void *out)
{
	const struct mtk_sha_reqctx *ctx = ahash_request_ctx(req);

	memcpy(out, ctx, sizeof(*ctx));
	return 0;
}