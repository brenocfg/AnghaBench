#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct rsocket {TYPE_3__* cm_id; } ;
struct ibv_sge {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_5__ {TYPE_1__ rdma; } ;
struct ibv_send_wr {int num_sge; int send_flags; TYPE_2__ wr; int /*<<< orphan*/  opcode; struct ibv_sge* sg_list; int /*<<< orphan*/ * next; int /*<<< orphan*/  wr_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_WR_RDMA_WRITE ; 
 int /*<<< orphan*/  ibv_post_send (int /*<<< orphan*/ ,struct ibv_send_wr*,struct ibv_send_wr**) ; 
 int rdma_seterrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_send_wr_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_post_write(struct rsocket *rs,
			 struct ibv_sge *sgl, int nsge,
			 uint32_t wr_data, int flags,
			 uint64_t addr, uint32_t rkey)
{
	struct ibv_send_wr wr, *bad;

	wr.wr_id = rs_send_wr_id(wr_data);
	wr.next = NULL;
	wr.sg_list = sgl;
	wr.num_sge = nsge;
	wr.opcode = IBV_WR_RDMA_WRITE;
	wr.send_flags = flags;
	wr.wr.rdma.remote_addr = addr;
	wr.wr.rdma.rkey = rkey;

	return rdma_seterrno(ibv_post_send(rs->cm_id->qp, &wr, &bad));
}