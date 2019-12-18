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
struct qlnxr_qp {scalar_t__ icid; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct qlnxr_create_qp_uresp {scalar_t__ sq_icid; int /*<<< orphan*/  sq_db_offset; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_ADDR_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_XCM_RDMA_SQ_PROD ; 
 scalar_t__ QLNX_IS_IWARP (struct qlnxr_dev*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
qlnxr_copy_sq_uresp(struct qlnxr_dev *dev,
	struct qlnxr_create_qp_uresp *uresp,
	struct qlnxr_qp *qp)
{
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	uresp->sq_db_offset = DB_ADDR_SHIFT(DQ_PWM_OFFSET_XCM_RDMA_SQ_PROD);

	/* iWARP uses the same cid for rq and sq*/
	if (QLNX_IS_IWARP(dev)) {
		uresp->sq_icid = qp->icid;
		QL_DPRINT12(ha, "uresp->sq_icid = 0x%x\n", uresp->sq_icid);
	} else
		uresp->sq_icid = qp->icid + 1;

	QL_DPRINT12(ha, "exit\n");
	return;
}