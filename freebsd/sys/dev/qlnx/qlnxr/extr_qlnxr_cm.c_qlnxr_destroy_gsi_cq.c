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
struct qlnxr_dev {TYPE_1__* ha; int /*<<< orphan*/  rdma_ctx; } ;
struct qlnxr_cq {scalar_t__ icid; int /*<<< orphan*/  pbl; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct ecore_rdma_destroy_cq_out_params {int dummy; } ;
struct ecore_rdma_destroy_cq_in_params {scalar_t__ icid; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ecore_chain_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_rdma_destroy_cq (int /*<<< orphan*/ ,struct ecore_rdma_destroy_cq_in_params*,struct ecore_rdma_destroy_cq_out_params*) ; 
 struct qlnxr_cq* get_qlnxr_cq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlnxr_destroy_gsi_cq(struct qlnxr_dev *dev,
		struct ib_qp_init_attr *attrs)
{
	struct ecore_rdma_destroy_cq_in_params iparams;
	struct ecore_rdma_destroy_cq_out_params oparams;
	struct qlnxr_cq *cq;

	QL_DPRINT12(dev->ha, "enter\n");

	cq = get_qlnxr_cq((attrs->send_cq));
	iparams.icid = cq->icid;
	ecore_rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);
	ecore_chain_free(&dev->ha->cdev, &cq->pbl);

	cq = get_qlnxr_cq((attrs->recv_cq));
	/* if a dedicated recv_cq was used, delete it too */
	if (iparams.icid != cq->icid) {
		iparams.icid = cq->icid;
		ecore_rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);
		ecore_chain_free(&dev->ha->cdev, &cq->pbl);
	}

	QL_DPRINT12(dev->ha, "exit\n");

	return;
}