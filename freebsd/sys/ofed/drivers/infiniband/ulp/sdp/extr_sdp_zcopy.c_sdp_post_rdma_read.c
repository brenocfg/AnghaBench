#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct TYPE_7__ {struct rx_srcavail_state* rdma_inflight; } ;
struct sdp_sock {int /*<<< orphan*/  qp; TYPE_1__ tx_ring; } ;
struct rx_srcavail_state {int /*<<< orphan*/  busy; scalar_t__ used; scalar_t__ vaddr; TYPE_4__* fmr; TYPE_2__* umem; int /*<<< orphan*/  rkey; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {scalar_t__ remote_addr; int /*<<< orphan*/  rkey; } ;
struct TYPE_12__ {TYPE_5__ rdma; } ;
struct ib_send_wr {int num_sge; scalar_t__ send_flags; struct ib_sge* sg_list; TYPE_6__ wr; int /*<<< orphan*/  wr_id; int /*<<< orphan*/ * next; int /*<<< orphan*/  opcode; int /*<<< orphan*/ * member_0; } ;
struct TYPE_10__ {TYPE_3__* fmr; } ;
struct TYPE_9__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ ; 
 int /*<<< orphan*/  SDP_OP_RDMA ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,struct ib_send_wr**) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 

__attribute__((used)) static int sdp_post_rdma_read(struct socket *sk, struct rx_srcavail_state *rx_sa)
{
	struct sdp_sock *ssk = sdp_sk(sk);
	struct ib_send_wr *bad_wr;
	struct ib_send_wr wr = { NULL };
	struct ib_sge sge;

	wr.opcode = IB_WR_RDMA_READ;
	wr.next = NULL;
	wr.wr_id = SDP_OP_RDMA;
	wr.wr.rdma.rkey = rx_sa->rkey;
	wr.send_flags = 0;

	ssk->tx_ring.rdma_inflight = rx_sa;

	sge.addr = rx_sa->umem->offset;
	sge.length = rx_sa->umem->length;
	sge.lkey = rx_sa->fmr->fmr->lkey;

	wr.wr.rdma.remote_addr = rx_sa->vaddr + rx_sa->used;
	wr.num_sge = 1;
	wr.sg_list = &sge;
	rx_sa->busy++;

	wr.send_flags = IB_SEND_SIGNALED;

	return ib_post_send(ssk->qp, &wr, &bad_wr);
}