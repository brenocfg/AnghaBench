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
struct vectx {scalar_t__ vec_hashsz; int vec_status; int /*<<< orphan*/  vec_want; int /*<<< orphan*/  vec_path; int /*<<< orphan*/  vec_md; int /*<<< orphan*/  vec_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vectx*) ; 
 int ve_check_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
vectx_close(struct vectx *ctx)
{
	int rc;

	if (ctx->vec_hashsz == 0) {
		rc = ctx->vec_status;
	} else {
		rc = ve_check_hash(&ctx->vec_ctx, ctx->vec_md,
		    ctx->vec_path, ctx->vec_want, ctx->vec_hashsz);
	}
	free(ctx);
	return ((rc < 0) ? rc : 0);
}