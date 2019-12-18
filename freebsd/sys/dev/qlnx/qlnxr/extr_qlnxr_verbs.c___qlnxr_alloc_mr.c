#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qlnxr_pd {int /*<<< orphan*/  pd_id; } ;
struct TYPE_8__ {int itid; int key; int local_read; int mw_bind; int zbva; int phy_mr; int dma_mr; scalar_t__ vaddr; scalar_t__ length; scalar_t__ fbo; int /*<<< orphan*/  pbl_page_size_log; int /*<<< orphan*/  pbl_two_level; scalar_t__ pbl_ptr; scalar_t__ remote_atomic; scalar_t__ remote_write; scalar_t__ remote_read; scalar_t__ local_write; int /*<<< orphan*/  pd; int /*<<< orphan*/  tid_type; } ;
struct TYPE_6__ {int lkey; int rkey; } ;
struct TYPE_5__ {int /*<<< orphan*/  pbl_size; int /*<<< orphan*/  two_layered; } ;
struct TYPE_7__ {TYPE_1__ pbl_info; } ;
struct qlnxr_mr {TYPE_4__ hw_mr; TYPE_2__ ibmr; TYPE_3__ info; int /*<<< orphan*/  type; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/ * ha; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_RDMA_TID_FMR ; 
 int ENOMEM ; 
 struct qlnxr_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QLNXR_MR_FRMR ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int ecore_rdma_alloc_tid (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ecore_rdma_free_tid (int /*<<< orphan*/ ,int) ; 
 int ecore_rdma_register_tid (int /*<<< orphan*/ ,TYPE_4__*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_pd* get_qlnxr_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_mr*) ; 
 struct qlnxr_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qlnxr_init_mr_info (struct qlnxr_dev*,TYPE_3__*,int,int) ; 

__attribute__((used)) static struct qlnxr_mr *
__qlnxr_alloc_mr(struct ib_pd *ibpd, int max_page_list_len)
{
	struct qlnxr_pd *pd = get_qlnxr_pd(ibpd);
	struct qlnxr_dev *dev = get_qlnxr_dev((ibpd->device));
	struct qlnxr_mr *mr;
	int		rc = -ENOMEM;
	qlnx_host_t	*ha;

	ha = dev->ha;
 
	QL_DPRINT12(ha, "enter ibpd = %p pd = %p "
		" pd_id = %d max_page_list_len = %d\n",
		ibpd, pd, pd->pd_id, max_page_list_len);

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr) {
		QL_DPRINT11(ha, "kzalloc(mr) failed\n");
		return ERR_PTR(rc);
	}

	mr->dev = dev;
	mr->type = QLNXR_MR_FRMR;

	rc = qlnxr_init_mr_info(dev, &mr->info, max_page_list_len,
				  1 /* allow dual layer pbl */);
	if (rc) {
		QL_DPRINT11(ha, "qlnxr_init_mr_info failed\n");
		goto err0;
	}

	rc = ecore_rdma_alloc_tid(dev->rdma_ctx, &mr->hw_mr.itid);
	if (rc) {
		QL_DPRINT11(ha, "ecore_rdma_alloc_tid failed\n");
		goto err0;
	}

	/* index only, 18 bit long, lkey = itid << 8 | key */
	mr->hw_mr.tid_type = ECORE_RDMA_TID_FMR;
	mr->hw_mr.key = 0;
	mr->hw_mr.pd = pd->pd_id;
	mr->hw_mr.local_read = 1;
	mr->hw_mr.local_write = 0;
	mr->hw_mr.remote_read = 0;
	mr->hw_mr.remote_write = 0;
	mr->hw_mr.remote_atomic = 0;
	mr->hw_mr.mw_bind = false; /* TBD MW BIND */
	mr->hw_mr.pbl_ptr = 0; /* Will be supplied during post */
	mr->hw_mr.pbl_two_level = mr->info.pbl_info.two_layered;
	mr->hw_mr.pbl_page_size_log = ilog2(mr->info.pbl_info.pbl_size);
	mr->hw_mr.fbo = 0;
	mr->hw_mr.length = 0;
	mr->hw_mr.vaddr = 0;
	mr->hw_mr.zbva = false; /* TBD figure when this should be true */
	mr->hw_mr.phy_mr = true; /* Fast MR - True, Regular Register False */
	mr->hw_mr.dma_mr = false;

	rc = ecore_rdma_register_tid(dev->rdma_ctx, &mr->hw_mr);
	if (rc) {
		QL_DPRINT11(ha, "ecore_rdma_register_tid failed\n");
		goto err1;
	}

	mr->ibmr.lkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;
	mr->ibmr.rkey = mr->ibmr.lkey;

	QL_DPRINT12(ha, "exit mr = %p mr->ibmr.lkey = 0x%x\n",
		mr, mr->ibmr.lkey);

	return mr;

err1:
	ecore_rdma_free_tid(dev->rdma_ctx, mr->hw_mr.itid);
err0:
	kfree(mr);

	QL_DPRINT12(ha, "exit\n");

	return ERR_PTR(rc);
}