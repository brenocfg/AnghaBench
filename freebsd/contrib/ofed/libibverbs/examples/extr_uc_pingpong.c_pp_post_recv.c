#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pingpong_context {int /*<<< orphan*/  qp; TYPE_1__* mr; int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct ibv_sge {uintptr_t addr; int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; } ;
struct ibv_recv_wr {int num_sge; struct ibv_sge* sg_list; int /*<<< orphan*/  wr_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  PINGPONG_RECV_WRID ; 
 scalar_t__ ibv_post_recv (int /*<<< orphan*/ ,struct ibv_recv_wr*,struct ibv_recv_wr**) ; 

__attribute__((used)) static int pp_post_recv(struct pingpong_context *ctx, int n)
{
	struct ibv_sge list = {
		.addr	= (uintptr_t) ctx->buf,
		.length = ctx->size,
		.lkey	= ctx->mr->lkey
	};
	struct ibv_recv_wr wr = {
		.wr_id	    = PINGPONG_RECV_WRID,
		.sg_list    = &list,
		.num_sge    = 1,
	};
	struct ibv_recv_wr *bad_wr;
	int i;

	for (i = 0; i < n; ++i)
		if (ibv_post_recv(ctx->qp, &wr, &bad_wr))
			break;

	return i;
}