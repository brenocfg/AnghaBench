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
struct TYPE_6__ {int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  ah; } ;
struct TYPE_7__ {TYPE_1__ ud; } ;
struct ibv_send_wr {int num_sge; int send_flags; unsigned long wr_id; TYPE_2__ wr; int /*<<< orphan*/  imm_data; int /*<<< orphan*/  opcode; struct ibv_sge* sg_list; int /*<<< orphan*/ * next; } ;
struct cmatest_node {TYPE_4__* cma_id; scalar_t__ mem; TYPE_3__* mr; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  ah; int /*<<< orphan*/  connected; } ;
struct TYPE_10__ {int /*<<< orphan*/  qp_num; } ;
struct TYPE_9__ {TYPE_5__* qp; } ;
struct TYPE_8__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_WR_SEND_WITH_IMM ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int ibv_post_send (TYPE_5__*,struct ibv_send_wr*,struct ibv_send_wr**) ; 
 int message_count ; 
 int /*<<< orphan*/  message_size ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int post_sends(struct cmatest_node *node, int signal_flag)
{
	struct ibv_send_wr send_wr, *bad_send_wr;
	struct ibv_sge sge;
	int i, ret = 0;

	if (!node->connected || !message_count)
		return 0;

	send_wr.next = NULL;
	send_wr.sg_list = &sge;
	send_wr.num_sge = 1;
	send_wr.opcode = IBV_WR_SEND_WITH_IMM;
	send_wr.send_flags = signal_flag;
	send_wr.wr_id = (unsigned long)node;
	send_wr.imm_data = htobe32(node->cma_id->qp->qp_num);

	send_wr.wr.ud.ah = node->ah;
	send_wr.wr.ud.remote_qpn = node->remote_qpn;
	send_wr.wr.ud.remote_qkey = node->remote_qkey;

	sge.length = message_size;
	sge.lkey = node->mr->lkey;
	sge.addr = (uintptr_t) node->mem;

	for (i = 0; i < message_count && !ret; i++) {
		ret = ibv_post_send(node->cma_id->qp, &send_wr, &bad_send_wr);
		if (ret)
			printf("failed to post sends: %d\n", ret);
	}
	return ret;
}