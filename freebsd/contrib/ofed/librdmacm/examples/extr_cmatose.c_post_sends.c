#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_sge {uintptr_t addr; int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; } ;
struct ibv_send_wr {int num_sge; unsigned long wr_id; scalar_t__ send_flags; int /*<<< orphan*/  opcode; struct ibv_sge* sg_list; int /*<<< orphan*/ * next; } ;
struct cmatest_node {TYPE_2__* cma_id; scalar_t__ mem; TYPE_1__* mr; int /*<<< orphan*/  connected; } ;
struct TYPE_4__ {int /*<<< orphan*/  qp; } ;
struct TYPE_3__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_WR_SEND ; 
 int ibv_post_send (int /*<<< orphan*/ ,struct ibv_send_wr*,struct ibv_send_wr**) ; 
 int message_count ; 
 int /*<<< orphan*/  message_size ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int post_sends(struct cmatest_node *node)
{
	struct ibv_send_wr send_wr, *bad_send_wr;
	struct ibv_sge sge;
	int i, ret = 0;

	if (!node->connected || !message_count)
		return 0;

	send_wr.next = NULL;
	send_wr.sg_list = &sge;
	send_wr.num_sge = 1;
	send_wr.opcode = IBV_WR_SEND;
	send_wr.send_flags = 0;
	send_wr.wr_id = (unsigned long)node;

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