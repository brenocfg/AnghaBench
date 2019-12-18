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
struct qlnxr_pd {int /*<<< orphan*/  pd_id; } ;
struct TYPE_2__ {int itid; int local_read; int local_write; int remote_read; int remote_write; int remote_atomic; int dma_mr; int key; int /*<<< orphan*/  pd; int /*<<< orphan*/  tid_type; } ;
struct ib_mr {int lkey; int rkey; } ;
struct qlnxr_mr {TYPE_1__ hw_mr; struct ib_mr ibmr; int /*<<< orphan*/  type; } ;
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/ * ha; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_RDMA_TID_REGISTERED_MR ; 
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_MW_BIND ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  QLNXR_MR_DMA ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int ecore_rdma_alloc_tid (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ecore_rdma_free_tid (int /*<<< orphan*/ ,int) ; 
 int ecore_rdma_register_tid (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_pd* get_qlnxr_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_mr*) ; 
 struct qlnxr_mr* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ib_mr *
qlnxr_get_dma_mr(struct ib_pd *ibpd, int acc)
{
	struct qlnxr_mr		*mr;
	struct qlnxr_dev	*dev = get_qlnxr_dev((ibpd->device));
	struct qlnxr_pd		*pd = get_qlnxr_pd(ibpd);
	int			rc;
	qlnx_host_t		*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	if (acc & IB_ACCESS_MW_BIND) {
		QL_DPRINT12(ha, "Unsupported access flags received for dma mr\n");
	}

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr) {
		rc = -ENOMEM;
		QL_DPRINT12(ha, "kzalloc(mr) failed %d\n", rc);
		goto err0;
	}

	mr->type = QLNXR_MR_DMA;

	rc = ecore_rdma_alloc_tid(dev->rdma_ctx, &mr->hw_mr.itid);
	if (rc) {
		QL_DPRINT12(ha, "ecore_rdma_alloc_tid failed %d\n", rc);
		goto err1;
	}

	/* index only, 18 bit long, lkey = itid << 8 | key */
	mr->hw_mr.tid_type = ECORE_RDMA_TID_REGISTERED_MR;
	mr->hw_mr.pd = pd->pd_id;
	mr->hw_mr.local_read = 1;
	mr->hw_mr.local_write = (acc & IB_ACCESS_LOCAL_WRITE) ? 1 : 0;
	mr->hw_mr.remote_read = (acc & IB_ACCESS_REMOTE_READ) ? 1 : 0;
	mr->hw_mr.remote_write = (acc & IB_ACCESS_REMOTE_WRITE) ? 1 : 0;
	mr->hw_mr.remote_atomic = (acc & IB_ACCESS_REMOTE_ATOMIC) ? 1 : 0;
	mr->hw_mr.dma_mr = true;

	rc = ecore_rdma_register_tid(dev->rdma_ctx, &mr->hw_mr);
	if (rc) {
		QL_DPRINT12(ha, "ecore_rdma_register_tid failed %d\n", rc);
		goto err2;
	}

	mr->ibmr.lkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;

	if (mr->hw_mr.remote_write || mr->hw_mr.remote_read ||
		mr->hw_mr.remote_atomic) {
		mr->ibmr.rkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;
	}

	QL_DPRINT12(ha, "lkey = %x\n", mr->ibmr.lkey);

	return &mr->ibmr;

err2:
	ecore_rdma_free_tid(dev->rdma_ctx, mr->hw_mr.itid);
err1:
	kfree(mr);
err0:
	QL_DPRINT12(ha, "exit [%d]\n", rc);

	return ERR_PTR(rc);
}