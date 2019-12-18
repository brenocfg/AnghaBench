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
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/ * ha; } ;
struct TYPE_2__ {scalar_t__ max_wr; scalar_t__ max_sge; scalar_t__ srq_limit; } ;
struct ib_srq_init_attr {TYPE_1__ attr; } ;
struct ib_pd {int dummy; } ;
struct ecore_rdma_device {scalar_t__ max_srq_wqe; scalar_t__ max_sge; int /*<<< orphan*/  max_srq_wr; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 struct ecore_rdma_device* ecore_rdma_query_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnxr_check_srq_params(struct ib_pd *ibpd,
	struct qlnxr_dev *dev,
	struct ib_srq_init_attr *attrs)
{
	struct ecore_rdma_device *qattr;
	qlnx_host_t		*ha;

	ha = dev->ha;
	qattr = ecore_rdma_query_device(dev->rdma_ctx);

	QL_DPRINT12(ha, "enter\n");

	if (attrs->attr.max_wr > qattr->max_srq_wqe) {
		QL_DPRINT12(ha, "unsupported srq_wr=0x%x"
			" requested (max_srq_wr=0x%x)\n",
			attrs->attr.max_wr, qattr->max_srq_wr);
		return -EINVAL;
	}

	if (attrs->attr.max_sge > qattr->max_sge) {
		QL_DPRINT12(ha,
			"unsupported sge=0x%x requested (max_srq_sge=0x%x)\n",
			attrs->attr.max_sge, qattr->max_sge);
		return -EINVAL;
	}

	if (attrs->attr.srq_limit > attrs->attr.max_wr) {
		QL_DPRINT12(ha,
		       "unsupported srq_limit=0x%x requested"
			" (max_srq_limit=0x%x)\n",
			attrs->attr.srq_limit, attrs->attr.srq_limit);
		return -EINVAL;
	}

	QL_DPRINT12(ha, "exit\n");
	return 0;
}