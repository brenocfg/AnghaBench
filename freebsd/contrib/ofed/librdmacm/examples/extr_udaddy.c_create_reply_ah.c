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
struct ibv_wc {int /*<<< orphan*/  imm_data; } ;
struct ibv_qp_init_attr {int dummy; } ;
struct ibv_qp_attr {int /*<<< orphan*/  qkey; } ;
struct cmatest_node {int /*<<< orphan*/  remote_qkey; TYPE_1__* cma_id; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  mem; int /*<<< orphan*/  pd; int /*<<< orphan*/  ah; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp; int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QP_QKEY ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_create_ah_from_wc (int /*<<< orphan*/ ,struct ibv_wc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_query_qp (int /*<<< orphan*/ ,struct ibv_qp_attr*,int /*<<< orphan*/ ,struct ibv_qp_init_attr*) ; 

__attribute__((used)) static void create_reply_ah(struct cmatest_node *node, struct ibv_wc *wc)
{
	struct ibv_qp_attr attr;
	struct ibv_qp_init_attr init_attr;

	node->ah = ibv_create_ah_from_wc(node->pd, wc, node->mem,
					 node->cma_id->port_num);
	node->remote_qpn = be32toh(wc->imm_data);

	ibv_query_qp(node->cma_id->qp, &attr, IBV_QP_QKEY, &init_attr);
	node->remote_qkey = attr.qkey;
}