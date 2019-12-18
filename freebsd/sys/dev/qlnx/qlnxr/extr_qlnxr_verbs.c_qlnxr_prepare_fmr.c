#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_14__ {void* lo; void* hi; } ;
struct rdma_sq_fmr_wqe_1st {TYPE_4__ addr; int /*<<< orphan*/  l_key; } ;
struct TYPE_15__ {void* lo; void* hi; } ;
struct rdma_sq_fmr_wqe {TYPE_5__ pbl_addr; int /*<<< orphan*/  length_lo; scalar_t__ length_hi; scalar_t__ fmr_ctrl; scalar_t__ access_ctrl; } ;
struct TYPE_17__ {size_t prod; int /*<<< orphan*/  pbl; } ;
struct qlnxr_qp {TYPE_7__ sq; TYPE_6__* wqe_wr_id; struct qlnxr_dev* dev; } ;
struct TYPE_18__ {TYPE_1__* pbl_table; } ;
struct qlnxr_fast_reg_page_list {TYPE_8__ info; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct TYPE_12__ {scalar_t__ page_list_len; int access_flags; int page_shift; int /*<<< orphan*/  rkey; int /*<<< orphan*/  iova_start; TYPE_9__* page_list; int /*<<< orphan*/  length; } ;
struct TYPE_13__ {TYPE_2__ fast_reg; } ;
struct ib_send_wr {TYPE_3__ wr; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_19__ {int* page_list; } ;
struct TYPE_16__ {struct qlnxr_fast_reg_page_list* frmr; } ;
struct TYPE_11__ {int /*<<< orphan*/  pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  RDMA_SQ_FMR_WQE_2ND_PAGE_SIZE_LOG ; 
 int /*<<< orphan*/  RDMA_SQ_FMR_WQE_2ND_ZERO_BASED ; 
 int /*<<< orphan*/  RDMA_SQ_FMR_WQE_ENABLE_ATOMIC ; 
 int /*<<< orphan*/  RDMA_SQ_FMR_WQE_LOCAL_READ ; 
 int /*<<< orphan*/  RDMA_SQ_FMR_WQE_LOCAL_WRITE ; 
 int /*<<< orphan*/  RDMA_SQ_FMR_WQE_REMOTE_READ ; 
 int /*<<< orphan*/  RDMA_SQ_FMR_WQE_REMOTE_WRITE ; 
 int /*<<< orphan*/  SET_FIELD2 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_frmr_pbes (struct qlnxr_dev*,struct ib_send_wr*,TYPE_8__*) ; 
 scalar_t__ ecore_chain_produce (int /*<<< orphan*/ *) ; 
 struct qlnxr_fast_reg_page_list* get_qlnxr_frmr_list (TYPE_9__*) ; 
 int ilog2 (int) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int qlnxr_prepare_safe_pbl (struct qlnxr_dev*,TYPE_8__*) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
qlnxr_prepare_fmr(struct qlnxr_qp *qp,
	struct rdma_sq_fmr_wqe_1st *fwqe1,
	struct ib_send_wr *wr)
{
	struct qlnxr_dev *dev = qp->dev;
	u64 fbo;
	struct qlnxr_fast_reg_page_list *frmr_list =
		get_qlnxr_frmr_list(wr->wr.fast_reg.page_list);
	struct rdma_sq_fmr_wqe *fwqe2 =
		(struct rdma_sq_fmr_wqe *)ecore_chain_produce(&qp->sq.pbl);
	int rc = 0;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");
 
	if (wr->wr.fast_reg.page_list_len == 0)
		BUG();

	rc = qlnxr_prepare_safe_pbl(dev, &frmr_list->info);
	if (rc)
		return rc;

	fwqe1->addr.hi = upper_32_bits(wr->wr.fast_reg.iova_start);
	fwqe1->addr.lo = lower_32_bits(wr->wr.fast_reg.iova_start);
	fwqe1->l_key = wr->wr.fast_reg.rkey;

	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_REMOTE_READ,
		   !!(wr->wr.fast_reg.access_flags & IB_ACCESS_REMOTE_READ));
	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_REMOTE_WRITE,
		   !!(wr->wr.fast_reg.access_flags & IB_ACCESS_REMOTE_WRITE));
	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_ENABLE_ATOMIC,
		   !!(wr->wr.fast_reg.access_flags & IB_ACCESS_REMOTE_ATOMIC));
	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_LOCAL_READ, 1);
	SET_FIELD2(fwqe2->access_ctrl, RDMA_SQ_FMR_WQE_LOCAL_WRITE,
		   !!(wr->wr.fast_reg.access_flags & IB_ACCESS_LOCAL_WRITE));

	fwqe2->fmr_ctrl = 0;

	SET_FIELD2(fwqe2->fmr_ctrl, RDMA_SQ_FMR_WQE_2ND_PAGE_SIZE_LOG,
		   ilog2(1 << wr->wr.fast_reg.page_shift) - 12);
	SET_FIELD2(fwqe2->fmr_ctrl, RDMA_SQ_FMR_WQE_2ND_ZERO_BASED, 0);

	fwqe2->length_hi = 0; /* Todo - figure this out... why length is only 32bit.. */
	fwqe2->length_lo = wr->wr.fast_reg.length;
	fwqe2->pbl_addr.hi = upper_32_bits(frmr_list->info.pbl_table->pa);
	fwqe2->pbl_addr.lo = lower_32_bits(frmr_list->info.pbl_table->pa);

	/* produce another wqe for fwqe3 */
	ecore_chain_produce(&qp->sq.pbl);

	fbo = wr->wr.fast_reg.iova_start -
	    (wr->wr.fast_reg.page_list->page_list[0] & PAGE_MASK);

	QL_DPRINT12(ha, "wr.fast_reg.iova_start = %p rkey=%x addr=%x:%x"
		" length = %x pbl_addr %x:%x\n",
		wr->wr.fast_reg.iova_start, wr->wr.fast_reg.rkey,
		fwqe1->addr.hi, fwqe1->addr.lo, fwqe2->length_lo,
		fwqe2->pbl_addr.hi, fwqe2->pbl_addr.lo);

	build_frmr_pbes(dev, wr, &frmr_list->info);

	qp->wqe_wr_id[qp->sq.prod].frmr = frmr_list;

	QL_DPRINT12(ha, "exit\n");
	return 0;
}