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
struct qlnxr_qp {int /*<<< orphan*/  qp_id; TYPE_1__* dev; int /*<<< orphan*/  refcnt; } ;
struct ib_qp {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct qlnxr_qp* get_qlnxr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_qp*) ; 
 int /*<<< orphan*/  qlnxr_idr_remove (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
qlnxr_iw_qp_rem_ref(struct ib_qp *ibqp)
{
	struct qlnxr_qp *qp = get_qlnxr_qp(ibqp);
	qlnx_host_t	*ha;

	ha = qp->dev->ha;

	QL_DPRINT12(ha, "enter ibqp = %p qp = %p\n", ibqp, qp);

	if (atomic_dec_and_test(&qp->refcnt)) {
		qlnxr_idr_remove(qp->dev, qp->qp_id);
		kfree(qp);
	}

	QL_DPRINT12(ha, "exit \n");
	return;
}