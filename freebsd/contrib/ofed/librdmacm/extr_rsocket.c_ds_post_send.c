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
typedef  int /*<<< orphan*/  uint32_t ;
struct rsocket {scalar_t__ sq_inline; TYPE_5__* conn_dest; } ;
struct ibv_sge {scalar_t__ length; } ;
struct TYPE_6__ {int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  ah; } ;
struct TYPE_7__ {TYPE_1__ ud; } ;
struct ibv_send_wr {int num_sge; TYPE_2__ wr; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; struct ibv_sge* sg_list; int /*<<< orphan*/ * next; int /*<<< orphan*/  wr_id; } ;
struct TYPE_10__ {TYPE_4__* qp; int /*<<< orphan*/  qpn; int /*<<< orphan*/  ah; } ;
struct TYPE_9__ {TYPE_3__* cm_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_SEND_INLINE ; 
 int /*<<< orphan*/  IBV_WR_SEND ; 
 int /*<<< orphan*/  RDMA_UDP_QKEY ; 
 int /*<<< orphan*/  ibv_post_send (int /*<<< orphan*/ ,struct ibv_send_wr*,struct ibv_send_wr**) ; 
 int rdma_seterrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_send_wr_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_post_send(struct rsocket *rs, struct ibv_sge *sge,
			uint32_t wr_data)
{
	struct ibv_send_wr wr, *bad;

	wr.wr_id = rs_send_wr_id(wr_data);
	wr.next = NULL;
	wr.sg_list = sge;
	wr.num_sge = 1;
	wr.opcode = IBV_WR_SEND;
	wr.send_flags = (sge->length <= rs->sq_inline) ? IBV_SEND_INLINE : 0;
	wr.wr.ud.ah = rs->conn_dest->ah;
	wr.wr.ud.remote_qpn = rs->conn_dest->qpn;
	wr.wr.ud.remote_qkey = RDMA_UDP_QKEY;

	return rdma_seterrno(ibv_post_send(rs->conn_dest->qp->cm_id->qp, &wr, &bad));
}