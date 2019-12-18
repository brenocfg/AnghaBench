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
typedef  int u8 ;
typedef  int u32 ;
struct rdma_sq_sge {void* length; void* l_key; } ;
struct TYPE_3__ {int /*<<< orphan*/  pbl; } ;
struct qlnxr_qp {TYPE_1__ sq; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_send_wr {int num_sge; TYPE_2__* sg_list; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_4__ {scalar_t__ length; scalar_t__ lkey; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TYPEPTR_ADDR_SET (struct rdma_sq_sge*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addr ; 
 void* cpu_to_le32 (scalar_t__) ; 
 struct rdma_sq_sge* ecore_chain_produce (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
qlnxr_prepare_sq_sges(struct qlnxr_dev *dev, struct qlnxr_qp *qp,
	u8 *wqe_size, struct ib_send_wr *wr)
{
	int i;
	u32 data_size = 0;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter wr->num_sge = %d \n", wr->num_sge);
 
	for (i = 0; i < wr->num_sge; i++) {
		struct rdma_sq_sge *sge = ecore_chain_produce(&qp->sq.pbl);

		TYPEPTR_ADDR_SET(sge, addr, wr->sg_list[i].addr);
		sge->l_key = cpu_to_le32(wr->sg_list[i].lkey);
		sge->length = cpu_to_le32(wr->sg_list[i].length);
		data_size += wr->sg_list[i].length;
	}

	if (wqe_size)
		*wqe_size += wr->num_sge;

	QL_DPRINT12(ha, "exit data_size = %d\n", data_size);
	return data_size;
}