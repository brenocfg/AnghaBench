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
struct s5p_hash_reqctx {scalar_t__ bufcnt; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (void*,struct s5p_hash_reqctx const*,scalar_t__) ; 

__attribute__((used)) static int s5p_hash_export(struct ahash_request *req, void *out)
{
	const struct s5p_hash_reqctx *ctx = ahash_request_ctx(req);

	memcpy(out, ctx, sizeof(*ctx) + ctx->bufcnt);

	return 0;
}