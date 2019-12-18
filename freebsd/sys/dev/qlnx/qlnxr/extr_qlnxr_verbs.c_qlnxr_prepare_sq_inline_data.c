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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct rdma_sq_common_wqe {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pbl; } ;
struct qlnxr_qp {TYPE_1__ sq; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_send_wr {int num_sge; TYPE_2__* sg_list; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_4__ {scalar_t__ length; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ ROCE_REQ_MAX_INLINE_DATA_SIZE ; 
 scalar_t__ ecore_chain_produce (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,void*,scalar_t__) ; 
 scalar_t__ sge_data_len (TYPE_2__*,int) ; 
 int /*<<< orphan*/  swap_wqe_data64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
qlnxr_prepare_sq_inline_data(struct qlnxr_dev *dev,
	struct qlnxr_qp		*qp,
	u8			*wqe_size,
	struct ib_send_wr	*wr,
	struct ib_send_wr	**bad_wr,
	u8			*bits,
	u8			bit)
{
	int i, seg_siz;
	char *seg_prt, *wqe;
	u32 data_size = sge_data_len(wr->sg_list, wr->num_sge);
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter[%d]\n", data_size);

	if (data_size > ROCE_REQ_MAX_INLINE_DATA_SIZE) {
		QL_DPRINT12(ha,
			"Too much inline data in WR:[%d, %d]\n",
			data_size, ROCE_REQ_MAX_INLINE_DATA_SIZE);
		*bad_wr = wr;
		return 0;
	}

	if (!data_size)
		return data_size;

	/* set the bit */
	*bits |= bit;

	seg_prt = wqe = NULL;
	seg_siz = 0;

	/* copy data inline */
	for (i = 0; i < wr->num_sge; i++) {
		u32 len = wr->sg_list[i].length;
		void *src = (void *)(uintptr_t)wr->sg_list[i].addr;

		while (len > 0) {
			u32 cur;

			/* new segment required */
			if (!seg_siz) {
				wqe = (char *)ecore_chain_produce(&qp->sq.pbl);
				seg_prt = wqe;
				seg_siz = sizeof(struct rdma_sq_common_wqe);
				(*wqe_size)++;
			}

			/* calculate currently allowed length */
			cur = MIN(len, seg_siz);

			memcpy(seg_prt, src, cur);

			/* update segment variables */
			seg_prt += cur;
			seg_siz -= cur;
			/* update sge variables */
			src += cur;
			len -= cur;

			/* swap fully-completed segments */
			if (!seg_siz)
				swap_wqe_data64((u64 *)wqe);
		}
	}

	/* swap last not completed segment */
	if (seg_siz)
		swap_wqe_data64((u64 *)wqe);

	QL_DPRINT12(ha, "exit\n");
	return data_size;
}