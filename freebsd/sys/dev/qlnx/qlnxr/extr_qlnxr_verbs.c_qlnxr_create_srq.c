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
typedef  int /*<<< orphan*/  ureq ;
typedef  void* u64 ;
typedef  void* u32 ;
struct qlnxr_ucontext {int dummy; } ;
struct ecore_chain {int elem_per_page; } ;
struct qlnxr_srq_hwq_info {void* phy_prod_pair_addr; struct ecore_chain pbl; } ;
struct ib_srq {int dummy; } ;
struct TYPE_7__ {void* num_pbes; } ;
struct TYPE_10__ {TYPE_4__* umem; TYPE_3__* pbl_tbl; TYPE_2__ pbl_info; } ;
struct qlnxr_srq {int /*<<< orphan*/  srq_id; struct ib_srq ibsrq; TYPE_5__ usrq; int /*<<< orphan*/  lock; struct qlnxr_srq_hwq_info hw_srq; struct qlnxr_dev* dev; } ;
struct qlnxr_pd {int /*<<< orphan*/  pd_id; } ;
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/ * ha; } ;
struct qlnxr_create_srq_ureq {void* page_size; void* num_pages; void* prod_pair_addr; void* pbl_base_addr; int /*<<< orphan*/  pd_id; } ;
struct ib_udata {int /*<<< orphan*/  inlen; } ;
struct ib_ucontext {int dummy; } ;
struct ib_srq_init_attr {int dummy; } ;
struct ib_pd {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct ecore_rdma_destroy_srq_in_params {int /*<<< orphan*/  srq_id; } ;
struct ecore_rdma_create_srq_out_params {int /*<<< orphan*/  srq_id; } ;
struct ecore_rdma_create_srq_in_params {void* page_size; void* num_pages; void* prod_pair_addr; void* pbl_base_addr; int /*<<< orphan*/  pd_id; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
typedef  int /*<<< orphan*/  in_params ;
struct TYPE_9__ {void* page_size; } ;
struct TYPE_8__ {void* pa; } ;
struct TYPE_6__ {struct ib_ucontext* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 struct ib_srq* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 void* ecore_chain_get_page_cnt (struct ecore_chain*) ; 
 void* ecore_chain_get_pbl_phys (struct ecore_chain*) ; 
 int ecore_rdma_create_srq (int /*<<< orphan*/ ,struct qlnxr_create_srq_ureq*,struct ecore_rdma_create_srq_out_params*) ; 
 int /*<<< orphan*/  ecore_rdma_destroy_srq (int /*<<< orphan*/ ,struct ecore_rdma_destroy_srq_in_params*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_pd* get_qlnxr_pd (struct ib_pd*) ; 
 struct qlnxr_ucontext* get_qlnxr_ucontext (struct ib_ucontext*) ; 
 scalar_t__ ib_copy_from_udata (struct qlnxr_create_srq_ureq*,struct ib_udata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_srq*) ; 
 struct qlnxr_srq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qlnxr_create_srq_ureq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int qlnxr_alloc_srq_kernel_params (struct qlnxr_srq*,struct qlnxr_dev*,struct ib_srq_init_attr*) ; 
 int qlnxr_check_srq_params (struct ib_pd*,struct qlnxr_dev*,struct ib_srq_init_attr*) ; 
 int qlnxr_copy_srq_uresp (struct qlnxr_dev*,struct qlnxr_srq*,struct ib_udata*) ; 
 int /*<<< orphan*/  qlnxr_free_srq_kernel_params (struct qlnxr_srq*) ; 
 int /*<<< orphan*/  qlnxr_free_srq_user_params (struct qlnxr_srq*) ; 
 int qlnxr_init_srq_user_params (struct ib_ucontext*,struct qlnxr_srq*,struct qlnxr_create_srq_ureq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ib_srq *
qlnxr_create_srq(struct ib_pd *ibpd, struct ib_srq_init_attr *init_attr,
	struct ib_udata *udata)
{
	struct qlnxr_dev	*dev;
	qlnx_host_t		*ha;
	struct ecore_rdma_destroy_srq_in_params destroy_in_params;
	struct ecore_rdma_create_srq_out_params out_params;
	struct ecore_rdma_create_srq_in_params in_params;
	u64 pbl_base_addr, phy_prod_pair_addr;
	struct qlnxr_pd *pd = get_qlnxr_pd(ibpd);
	struct ib_ucontext *ib_ctx = NULL;
	struct qlnxr_srq_hwq_info *hw_srq;
	struct qlnxr_ucontext *ctx = NULL;
	struct qlnxr_create_srq_ureq ureq;
	u32 page_cnt, page_size;
	struct qlnxr_srq *srq;
	int ret = 0;

	dev = get_qlnxr_dev((ibpd->device));
	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	ret = qlnxr_check_srq_params(ibpd, dev, init_attr);

	srq = kzalloc(sizeof(*srq), GFP_KERNEL);
	if (!srq) {
		QL_DPRINT11(ha, "cannot allocate memory for srq\n");
		return NULL; //@@@ : TODO what to return here?
	}

	srq->dev = dev;
	hw_srq = &srq->hw_srq;
	spin_lock_init(&srq->lock);
	memset(&in_params, 0, sizeof(in_params));

	if (udata && ibpd->uobject && ibpd->uobject->context) {
		ib_ctx = ibpd->uobject->context;
		ctx = get_qlnxr_ucontext(ib_ctx);

		memset(&ureq, 0, sizeof(ureq));
		if (ib_copy_from_udata(&ureq, udata, min(sizeof(ureq),
			udata->inlen))) {
			QL_DPRINT11(ha, "problem"
				" copying data from user space\n");
			goto err0;
		}

		ret = qlnxr_init_srq_user_params(ib_ctx, srq, &ureq, 0, 0);
		if (ret)
			goto err0;

		page_cnt = srq->usrq.pbl_info.num_pbes;
		pbl_base_addr = srq->usrq.pbl_tbl->pa;
		phy_prod_pair_addr = hw_srq->phy_prod_pair_addr;
		// @@@ : if DEFINE_IB_UMEM_PAGE_SHIFT
		// page_size = BIT(srq->usrq.umem->page_shift);
		// else
		page_size = srq->usrq.umem->page_size;
	} else {
		struct ecore_chain *pbl;
		ret = qlnxr_alloc_srq_kernel_params(srq, dev, init_attr);
		if (ret)
			goto err0;
		pbl = &hw_srq->pbl;

		page_cnt = ecore_chain_get_page_cnt(pbl);
		pbl_base_addr = ecore_chain_get_pbl_phys(pbl);
		phy_prod_pair_addr = hw_srq->phy_prod_pair_addr;
		page_size = pbl->elem_per_page << 4;
	}

	in_params.pd_id = pd->pd_id;
	in_params.pbl_base_addr = pbl_base_addr;
	in_params.prod_pair_addr = phy_prod_pair_addr;
	in_params.num_pages = page_cnt;
	in_params.page_size = page_size;

	ret = ecore_rdma_create_srq(dev->rdma_ctx, &in_params, &out_params);
	if (ret)
		goto err1;

	srq->srq_id = out_params.srq_id;

	if (udata) {
		ret = qlnxr_copy_srq_uresp(dev, srq, udata);
		if (ret)
			goto err2;
	}

	QL_DPRINT12(ha, "created srq with srq_id = 0x%0x\n", srq->srq_id);
	return &srq->ibsrq;
err2:
	memset(&in_params, 0, sizeof(in_params));
	destroy_in_params.srq_id = srq->srq_id;
	ecore_rdma_destroy_srq(dev->rdma_ctx, &destroy_in_params);

err1:
	if (udata)
		qlnxr_free_srq_user_params(srq);
	else
		qlnxr_free_srq_kernel_params(srq);

err0:
	kfree(srq);	
	return ERR_PTR(-EFAULT);
}