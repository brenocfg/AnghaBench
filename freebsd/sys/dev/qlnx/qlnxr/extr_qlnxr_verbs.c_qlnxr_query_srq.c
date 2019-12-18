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
struct qlnxr_srq {struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/ * ha; } ;
struct ib_srq_attr {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; int /*<<< orphan*/  srq_limit; } ;
struct ib_srq {int dummy; } ;
struct ecore_rdma_device {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 struct ecore_rdma_device* ecore_rdma_query_device (int /*<<< orphan*/ ) ; 
 struct qlnxr_srq* get_qlnxr_srq (struct ib_srq*) ; 

int
qlnxr_query_srq(struct ib_srq *ibsrq, struct ib_srq_attr *srq_attr)
{
	struct qlnxr_dev	*dev;
	struct qlnxr_srq	*srq;
	qlnx_host_t		*ha;
	struct ecore_rdma_device *qattr;
	srq = get_qlnxr_srq(ibsrq);
	dev = srq->dev;
	ha = dev->ha;
	//qattr = &dev->attr;
	qattr = ecore_rdma_query_device(dev->rdma_ctx);
	QL_DPRINT12(ha, "enter\n");

	if (!dev->rdma_ctx) {
		QL_DPRINT12(ha, "called with invalid params"
			" rdma_ctx is NULL\n");
		return -EINVAL;
	}

	srq_attr->srq_limit = qattr->max_srq;
	srq_attr->max_wr = qattr->max_srq_wr;
	srq_attr->max_sge = qattr->max_sge;

	QL_DPRINT12(ha, "exit\n");
	return 0;
}