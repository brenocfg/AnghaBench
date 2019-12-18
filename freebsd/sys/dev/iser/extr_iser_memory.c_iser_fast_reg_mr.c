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
struct iser_reg_resources {scalar_t__ mr_valid; struct ib_mr* mr; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; int /*<<< orphan*/  lkey; } ;
struct iser_mem_reg {TYPE_2__ sge; int /*<<< orphan*/  rkey; } ;
struct iser_device {int dummy; } ;
struct iser_data_buf {int dma_nents; int size; int /*<<< orphan*/  sg; } ;
struct icl_iser_pdu {TYPE_1__* iser_conn; } ;
struct ib_send_wr {struct ib_send_wr* next; scalar_t__ num_sge; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; } ;
struct ib_reg_wr {int access; struct ib_send_wr wr; int /*<<< orphan*/  key; struct ib_mr* mr; } ;
struct ib_mr {int /*<<< orphan*/  length; int /*<<< orphan*/  iova; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;
struct ib_conn {int /*<<< orphan*/  qp; struct iser_device* device; } ;
typedef  int /*<<< orphan*/  fastreg_wr ;
struct TYPE_3__ {struct ib_conn ib_conn; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  IB_WR_REG_MR ; 
 int /*<<< orphan*/  ISER_ERR (char*,int,...) ; 
 int /*<<< orphan*/  ISER_FASTREG_LI_WRID ; 
 int /*<<< orphan*/  SIZE_4K ; 
 int ib_map_mr_sg (struct ib_mr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,struct ib_send_wr**) ; 
 int /*<<< orphan*/  iser_inv_rkey (struct ib_send_wr*,struct ib_mr*) ; 
 int iser_reg_dma (struct iser_device*,struct iser_data_buf*,struct iser_mem_reg*) ; 
 int /*<<< orphan*/  memset (struct ib_reg_wr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
iser_fast_reg_mr(struct icl_iser_pdu *iser_pdu,
		 struct iser_data_buf *mem,
		 struct iser_reg_resources *rsc,
		 struct iser_mem_reg *reg)
{
	struct ib_conn *ib_conn = &iser_pdu->iser_conn->ib_conn;
	struct iser_device *device = ib_conn->device;
	struct ib_mr *mr = rsc->mr;
	struct ib_reg_wr fastreg_wr;
	struct ib_send_wr inv_wr;
	struct ib_send_wr *bad_wr, *wr = NULL;
	int ret, n;

	/* if there a single dma entry, dma mr suffices */
	if (mem->dma_nents == 1)
		return iser_reg_dma(device, mem, reg);

	if (!rsc->mr_valid) {
		iser_inv_rkey(&inv_wr, mr);
		wr = &inv_wr;
	}

	n = ib_map_mr_sg(mr, mem->sg, mem->size, NULL, SIZE_4K);
	if (unlikely(n != mem->size)) {
		ISER_ERR("failed to map sg (%d/%d)\n", n, mem->size);
		return n < 0 ? n : -EINVAL;
	}
	/* Prepare FASTREG WR */
	memset(&fastreg_wr, 0, sizeof(fastreg_wr));
	fastreg_wr.wr.opcode = IB_WR_REG_MR;
	fastreg_wr.wr.wr_id = ISER_FASTREG_LI_WRID;
	fastreg_wr.wr.num_sge = 0;
	fastreg_wr.mr = mr;
	fastreg_wr.key = mr->rkey;
	fastreg_wr.access = IB_ACCESS_LOCAL_WRITE  |
			    IB_ACCESS_REMOTE_WRITE |
			    IB_ACCESS_REMOTE_READ;

	if (!wr)
		wr = &fastreg_wr.wr;
	else
		wr->next = &fastreg_wr.wr;

	ret = ib_post_send(ib_conn->qp, wr, &bad_wr);
	if (ret) {
		ISER_ERR("fast registration failed, ret:%d", ret);
		return (ret);
	}
	rsc->mr_valid = 0;

	reg->sge.lkey = mr->lkey;
	reg->rkey = mr->rkey;
	reg->sge.addr = mr->iova;
	reg->sge.length = mr->length;

	return (ret);
}