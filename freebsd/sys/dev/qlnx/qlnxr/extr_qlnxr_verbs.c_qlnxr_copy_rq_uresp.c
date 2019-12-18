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
struct qlnxr_qp {int /*<<< orphan*/  icid; int /*<<< orphan*/  srq; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct qlnxr_create_qp_uresp {int /*<<< orphan*/  rq_icid; void* rq_db_offset; void* rq_db2_offset; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 void* DB_ADDR_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_TCM_FLAGS ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_TCM_IWARP_RQ_PROD ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_TCM_ROCE_RQ_PROD ; 
 scalar_t__ QLNX_IS_IWARP (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
qlnxr_copy_rq_uresp(struct qlnxr_dev *dev,
	struct qlnxr_create_qp_uresp *uresp,
	struct qlnxr_qp *qp)
{
	qlnx_host_t	*ha;

	ha = dev->ha;

	/* Return if QP is associated with SRQ instead of RQ */
	QL_DPRINT12(ha, "enter qp->srq = %p\n", qp->srq);

	if (qp->srq)
		return;

	/* iWARP requires two doorbells per RQ. */
	if (QLNX_IS_IWARP(dev)) {

		uresp->rq_db_offset =
			DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_IWARP_RQ_PROD);
		uresp->rq_db2_offset =
			DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_FLAGS);

		QL_DPRINT12(ha, "uresp->rq_db_offset = 0x%x "
			"uresp->rq_db2_offset = 0x%x\n",
			uresp->rq_db_offset, uresp->rq_db2_offset);
	} else {
		uresp->rq_db_offset =
			DB_ADDR_SHIFT(DQ_PWM_OFFSET_TCM_ROCE_RQ_PROD);
	}
	uresp->rq_icid = qp->icid;

	QL_DPRINT12(ha, "exit\n");
	return;
}