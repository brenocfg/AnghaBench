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
struct TYPE_4__ {int /*<<< orphan*/ * umem; } ;
struct TYPE_3__ {int /*<<< orphan*/ * umem; } ;
struct qlnxr_qp {TYPE_2__ urq; TYPE_1__ usq; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnxr_cleanup_user(struct qlnxr_dev *dev, struct qlnxr_qp *qp)
{
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");
 
	if (qp->usq.umem)
		ib_umem_release(qp->usq.umem);

	qp->usq.umem = NULL;

	if (qp->urq.umem)
		ib_umem_release(qp->urq.umem);

	qp->urq.umem = NULL;

	QL_DPRINT12(ha, "exit\n");
	return;
}