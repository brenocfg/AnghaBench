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
struct rdma_cm_id {struct ibv_pd* pd; } ;
struct ibv_qp_init_attr_ex {struct ibv_pd* pd; int /*<<< orphan*/  comp_mask; } ;
struct ibv_qp_init_attr {struct ibv_pd* pd; int /*<<< orphan*/  comp_mask; } ;
struct ibv_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QP_INIT_ATTR_PD ; 
 int /*<<< orphan*/  memcpy (struct ibv_qp_init_attr_ex*,struct ibv_qp_init_attr_ex*,int) ; 
 int rdma_create_qp_ex (struct rdma_cm_id*,struct ibv_qp_init_attr_ex*) ; 

int rdma_create_qp(struct rdma_cm_id *id, struct ibv_pd *pd,
		   struct ibv_qp_init_attr *qp_init_attr)
{
	struct ibv_qp_init_attr_ex attr_ex;
	int ret;

	memcpy(&attr_ex, qp_init_attr, sizeof(*qp_init_attr));
	attr_ex.comp_mask = IBV_QP_INIT_ATTR_PD;
	attr_ex.pd = pd ? pd : id->pd;
	ret = rdma_create_qp_ex(id, &attr_ex);
	memcpy(qp_init_attr, &attr_ex, sizeof(*qp_init_attr));
	return ret;
}