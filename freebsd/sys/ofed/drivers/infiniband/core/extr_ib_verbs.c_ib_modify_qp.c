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
struct ib_qp_attr {int /*<<< orphan*/  ah_attr; } ;
struct ib_qp {int /*<<< orphan*/  real_qp; TYPE_1__* device; } ;
struct TYPE_2__ {int (* modify_qp ) (int /*<<< orphan*/ ,struct ib_qp_attr*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int IB_QP_AV ; 
 int ib_resolve_eth_dmac (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct ib_qp_attr*,int,int /*<<< orphan*/ *) ; 

int ib_modify_qp(struct ib_qp *qp,
		 struct ib_qp_attr *qp_attr,
		 int qp_attr_mask)
{
	if (qp_attr_mask & IB_QP_AV) {
		int ret;

		ret = ib_resolve_eth_dmac(qp->device, &qp_attr->ah_attr);
		if (ret)
			return ret;
	}

	return qp->device->modify_qp(qp->real_qp, qp_attr, qp_attr_mask, NULL);
}