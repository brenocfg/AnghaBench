#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ibv_sge {uintptr_t addr; int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; } ;
struct TYPE_7__ {int /*<<< orphan*/  remote_srqn; } ;
struct TYPE_8__ {TYPE_2__ xrc; } ;
struct ibv_send_wr {uintptr_t wr_id; int num_sge; int /*<<< orphan*/  send_flags; TYPE_3__ qp_type; int /*<<< orphan*/  opcode; struct ibv_sge* sg_list; int /*<<< orphan*/ * next; } ;
struct TYPE_10__ {int num_clients; int num_tests; int /*<<< orphan*/ * send_qp; TYPE_4__* rem_dest; TYPE_1__* mr; int /*<<< orphan*/  size; scalar_t__ buf; } ;
struct TYPE_9__ {int pp_cnt; int /*<<< orphan*/  srqn; } ;
struct TYPE_6__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_SEND_SIGNALED ; 
 int /*<<< orphan*/  IBV_WR_SEND ; 
 TYPE_5__ ctx ; 
 int ibv_post_send (int /*<<< orphan*/ ,struct ibv_send_wr*,struct ibv_send_wr**) ; 

__attribute__((used)) static int pp_post_send(int index)
{
	struct ibv_sge sge;
	struct ibv_send_wr wr, *bad_wr;
	int qpi;

	sge.addr = (uintptr_t) ctx.buf;
	sge.length = ctx.size;
	sge.lkey = ctx.mr->lkey;

	wr.wr_id   = (uintptr_t) index;
	wr.next    = NULL;
	wr.sg_list = &sge;
	wr.num_sge = 1;
	wr.opcode  = IBV_WR_SEND;
	wr.qp_type.xrc.remote_srqn = ctx.rem_dest[index].srqn;

	qpi = (index + ctx.rem_dest[index].pp_cnt) % ctx.num_clients;
	wr.send_flags = (++ctx.rem_dest[index].pp_cnt >= ctx.num_tests) ?
			IBV_SEND_SIGNALED : 0;

	return ibv_post_send(ctx.send_qp[qpi], &wr, &bad_wr);
}