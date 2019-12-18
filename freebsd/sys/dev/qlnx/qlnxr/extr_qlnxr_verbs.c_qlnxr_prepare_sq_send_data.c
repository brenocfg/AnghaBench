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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rdma_sq_send_wqe {int /*<<< orphan*/  wqe_size; int /*<<< orphan*/  flags; } ;
struct qlnxr_qp {int dummy; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_send_wr {int send_flags; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int IB_SEND_INLINE ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  RDMA_SQ_SEND_WQE_INLINE_FLG ; 
 int /*<<< orphan*/  SET_FIELD2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct rdma_sq_send_wqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlnxr_prepare_sq_inline_data (struct qlnxr_dev*,struct qlnxr_qp*,int /*<<< orphan*/ *,struct ib_send_wr*,struct ib_send_wr**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_prepare_sq_sges (struct qlnxr_dev*,struct qlnxr_qp*,int /*<<< orphan*/ *,struct ib_send_wr*) ; 

__attribute__((used)) static u32
qlnxr_prepare_sq_send_data(struct qlnxr_dev *dev,
	struct qlnxr_qp *qp,
	struct rdma_sq_send_wqe *swqe,
	struct rdma_sq_send_wqe *swqe2,
	struct ib_send_wr *wr,
	struct ib_send_wr **bad_wr)
{
	qlnx_host_t	*ha;
	u32             ret = 0;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");
 
	memset(swqe2, 0, sizeof(*swqe2));

	if (wr->send_flags & IB_SEND_INLINE) {
		u8 flags = 0;
		SET_FIELD2(flags, RDMA_SQ_SEND_WQE_INLINE_FLG, 1);
		return qlnxr_prepare_sq_inline_data(dev, qp, &swqe->wqe_size,
				wr, bad_wr, &swqe->flags, flags);
	}

	ret = qlnxr_prepare_sq_sges(dev, qp, &swqe->wqe_size, wr);

	QL_DPRINT12(ha, "exit ret = 0x%x\n", ret);

	return (ret);
}