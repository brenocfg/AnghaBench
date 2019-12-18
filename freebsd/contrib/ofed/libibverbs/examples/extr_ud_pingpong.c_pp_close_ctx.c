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
struct pingpong_context {struct pingpong_context* buf; int /*<<< orphan*/  context; scalar_t__ channel; int /*<<< orphan*/  pd; int /*<<< orphan*/  ah; int /*<<< orphan*/  mr; int /*<<< orphan*/  cq; int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct pingpong_context*) ; 
 scalar_t__ ibv_close_device (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_dealloc_pd (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_dereg_mr (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_destroy_ah (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_destroy_comp_channel (scalar_t__) ; 
 scalar_t__ ibv_destroy_cq (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_destroy_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int pp_close_ctx(struct pingpong_context *ctx)
{
	if (ibv_destroy_qp(ctx->qp)) {
		fprintf(stderr, "Couldn't destroy QP\n");
		return 1;
	}

	if (ibv_destroy_cq(ctx->cq)) {
		fprintf(stderr, "Couldn't destroy CQ\n");
		return 1;
	}

	if (ibv_dereg_mr(ctx->mr)) {
		fprintf(stderr, "Couldn't deregister MR\n");
		return 1;
	}

	if (ibv_destroy_ah(ctx->ah)) {
		fprintf(stderr, "Couldn't destroy AH\n");
		return 1;
	}

	if (ibv_dealloc_pd(ctx->pd)) {
		fprintf(stderr, "Couldn't deallocate PD\n");
		return 1;
	}

	if (ctx->channel) {
		if (ibv_destroy_comp_channel(ctx->channel)) {
			fprintf(stderr, "Couldn't destroy completion channel\n");
			return 1;
		}
	}

	if (ibv_close_device(ctx->context)) {
		fprintf(stderr, "Couldn't release context\n");
		return 1;
	}

	free(ctx->buf);
	free(ctx);

	return 0;
}