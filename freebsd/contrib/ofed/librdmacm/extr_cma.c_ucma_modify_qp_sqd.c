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
struct rdma_cm_id {int /*<<< orphan*/  qp; } ;
struct ibv_qp_attr {int /*<<< orphan*/  qp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QPS_SQD ; 
 int /*<<< orphan*/  IBV_QP_STATE ; 
 int /*<<< orphan*/  ibv_modify_qp (int /*<<< orphan*/ ,struct ibv_qp_attr*,int /*<<< orphan*/ ) ; 
 int rdma_seterrno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucma_modify_qp_sqd(struct rdma_cm_id *id)
{
	struct ibv_qp_attr qp_attr;

	if (!id->qp)
		return 0;

	qp_attr.qp_state = IBV_QPS_SQD;
	return rdma_seterrno(ibv_modify_qp(id->qp, &qp_attr, IBV_QP_STATE));
}