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
typedef  int /*<<< orphan*/  uint32_t ;
struct rsocket {int opts; TYPE_1__* cm_id; } ;
struct ibv_sge {uintptr_t addr; int length; scalar_t__ lkey; } ;
struct ibv_send_wr {int num_sge; scalar_t__ send_flags; int /*<<< orphan*/  opcode; struct ibv_sge* sg_list; int /*<<< orphan*/  imm_data; int /*<<< orphan*/ * next; int /*<<< orphan*/  wr_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 scalar_t__ IBV_SEND_INLINE ; 
 int /*<<< orphan*/  IBV_WR_RDMA_WRITE_WITH_IMM ; 
 int /*<<< orphan*/  IBV_WR_SEND ; 
 int RS_OPT_MSG_SEND ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_post_send (int /*<<< orphan*/ ,struct ibv_send_wr*,struct ibv_send_wr**) ; 
 int rdma_seterrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_send_wr_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_post_msg(struct rsocket *rs, uint32_t msg)
{
	struct ibv_send_wr wr, *bad;
	struct ibv_sge sge;

	wr.wr_id = rs_send_wr_id(msg);
	wr.next = NULL;
	if (!(rs->opts & RS_OPT_MSG_SEND)) {
		wr.sg_list = NULL;
		wr.num_sge = 0;
		wr.opcode = IBV_WR_RDMA_WRITE_WITH_IMM;
		wr.send_flags = 0;
		wr.imm_data = htobe32(msg);
	} else {
		sge.addr = (uintptr_t) &msg;
		sge.lkey = 0;
		sge.length = sizeof msg;
		wr.sg_list = &sge;
		wr.num_sge = 1;
		wr.opcode = IBV_WR_SEND;
		wr.send_flags = IBV_SEND_INLINE;
	}

	return rdma_seterrno(ibv_post_send(rs->cm_id->qp, &wr, &bad));
}