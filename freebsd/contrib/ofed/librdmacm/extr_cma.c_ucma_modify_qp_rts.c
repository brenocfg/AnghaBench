#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct rdma_cm_id {int /*<<< orphan*/  qp; } ;
struct ibv_qp_attr {scalar_t__ max_rd_atomic; int /*<<< orphan*/  qp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QPS_RTS ; 
 scalar_t__ RDMA_MAX_INIT_DEPTH ; 
 int /*<<< orphan*/  ibv_modify_qp (int /*<<< orphan*/ ,struct ibv_qp_attr*,int) ; 
 int rdma_init_qp_attr (struct rdma_cm_id*,struct ibv_qp_attr*,int*) ; 
 int rdma_seterrno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucma_modify_qp_rts(struct rdma_cm_id *id, uint8_t init_depth)
{
	struct ibv_qp_attr qp_attr;
	int qp_attr_mask, ret;

	qp_attr.qp_state = IBV_QPS_RTS;
	ret = rdma_init_qp_attr(id, &qp_attr, &qp_attr_mask);
	if (ret)
		return ret;

	if (init_depth != RDMA_MAX_INIT_DEPTH)
		qp_attr.max_rd_atomic = init_depth;
	return rdma_seterrno(ibv_modify_qp(id->qp, &qp_attr, qp_attr_mask));
}