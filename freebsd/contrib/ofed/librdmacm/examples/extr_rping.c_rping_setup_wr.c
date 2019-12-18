#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_18__ {int num_sge; TYPE_8__* sg_list; void* send_flags; } ;
struct TYPE_17__ {int /*<<< orphan*/  lkey; void* addr; } ;
struct TYPE_15__ {int num_sge; TYPE_5__* sg_list; void* send_flags; int /*<<< orphan*/  opcode; } ;
struct TYPE_14__ {int length; int /*<<< orphan*/  lkey; void* addr; } ;
struct TYPE_12__ {int num_sge; TYPE_2__* sg_list; } ;
struct TYPE_11__ {int length; int /*<<< orphan*/  lkey; void* addr; } ;
struct rping_cb {TYPE_9__ rdma_sq_wr; TYPE_8__ rdma_sgl; TYPE_7__* rdma_mr; scalar_t__ rdma_buf; TYPE_6__ sq_wr; TYPE_5__ send_sgl; TYPE_4__* send_mr; int /*<<< orphan*/  send_buf; TYPE_3__ rq_wr; TYPE_2__ recv_sgl; TYPE_1__* recv_mr; int /*<<< orphan*/  recv_buf; } ;
struct TYPE_16__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_13__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_10__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 void* IBV_SEND_SIGNALED ; 
 int /*<<< orphan*/  IBV_WR_SEND ; 

__attribute__((used)) static void rping_setup_wr(struct rping_cb *cb)
{
	cb->recv_sgl.addr = (uint64_t) (unsigned long) &cb->recv_buf;
	cb->recv_sgl.length = sizeof cb->recv_buf;
	cb->recv_sgl.lkey = cb->recv_mr->lkey;
	cb->rq_wr.sg_list = &cb->recv_sgl;
	cb->rq_wr.num_sge = 1;

	cb->send_sgl.addr = (uint64_t) (unsigned long) &cb->send_buf;
	cb->send_sgl.length = sizeof cb->send_buf;
	cb->send_sgl.lkey = cb->send_mr->lkey;

	cb->sq_wr.opcode = IBV_WR_SEND;
	cb->sq_wr.send_flags = IBV_SEND_SIGNALED;
	cb->sq_wr.sg_list = &cb->send_sgl;
	cb->sq_wr.num_sge = 1;

	cb->rdma_sgl.addr = (uint64_t) (unsigned long) cb->rdma_buf;
	cb->rdma_sgl.lkey = cb->rdma_mr->lkey;
	cb->rdma_sq_wr.send_flags = IBV_SEND_SIGNALED;
	cb->rdma_sq_wr.sg_list = &cb->rdma_sgl;
	cb->rdma_sq_wr.num_sge = 1;
}