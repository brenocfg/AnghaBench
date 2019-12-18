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
struct pingpong_context {int /*<<< orphan*/ * qp; int /*<<< orphan*/  send_flags; TYPE_1__* mr; int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct ibv_sge {uintptr_t addr; int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; } ;
struct ibv_send_wr {int num_sge; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; struct ibv_sge* sg_list; int /*<<< orphan*/  wr_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_WR_SEND ; 
 int /*<<< orphan*/  PINGPONG_SEND_WRID ; 
 int ibv_post_send (int /*<<< orphan*/ ,struct ibv_send_wr*,struct ibv_send_wr**) ; 

__attribute__((used)) static int pp_post_send(struct pingpong_context *ctx, int qp_index)
{
	struct ibv_sge list = {
		.addr	= (uintptr_t) ctx->buf,
		.length = ctx->size,
		.lkey	= ctx->mr->lkey
	};
	struct ibv_send_wr wr = {
		.wr_id	    = PINGPONG_SEND_WRID,
		.sg_list    = &list,
		.num_sge    = 1,
		.opcode     = IBV_WR_SEND,
		.send_flags = ctx->send_flags,
	};
	struct ibv_send_wr *bad_wr;

	return ibv_post_send(ctx->qp[qp_index], &wr, &bad_wr);
}