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
struct pingpong_context {struct pingpong_context* buf; int /*<<< orphan*/  context; scalar_t__ channel; int /*<<< orphan*/  pd; int /*<<< orphan*/  mr; int /*<<< orphan*/  cq; int /*<<< orphan*/  srq; int /*<<< orphan*/ * qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct pingpong_context*) ; 
 scalar_t__ ibv_close_device (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_dealloc_pd (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_dereg_mr (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_destroy_comp_channel (scalar_t__) ; 
 scalar_t__ ibv_destroy_cq (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_destroy_qp (int /*<<< orphan*/ ) ; 
 scalar_t__ ibv_destroy_srq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int pp_close_ctx(struct pingpong_context *ctx, int num_qp)
{
	int i;

	for (i = 0; i < num_qp; ++i) {
		if (ibv_destroy_qp(ctx->qp[i])) {
			fprintf(stderr, "Couldn't destroy QP[%d]\n", i);
			return 1;
		}
	}

	if (ibv_destroy_srq(ctx->srq)) {
		fprintf(stderr, "Couldn't destroy SRQ\n");
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