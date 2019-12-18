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
typedef  int /*<<< orphan*/  uresp ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct qlnxr_create_cq_uresp {int /*<<< orphan*/  icid; int /*<<< orphan*/  db_offset; } ;
struct qlnxr_cq {int /*<<< orphan*/  icid; } ;
struct ib_udata {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_ADDR_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQ_PWM_OFFSET_UCM_RDMA_CQ_CONS_32BIT ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int ib_copy_to_udata (struct ib_udata*,struct qlnxr_create_cq_uresp*,int) ; 
 int /*<<< orphan*/  memset (struct qlnxr_create_cq_uresp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qlnxr_copy_cq_uresp(struct qlnxr_dev *dev,
	struct qlnxr_cq *cq, struct ib_udata *udata)
{
	struct qlnxr_create_cq_uresp	uresp;
	int				rc;
	qlnx_host_t			*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	memset(&uresp, 0, sizeof(uresp));

	uresp.db_offset = DB_ADDR_SHIFT(DQ_PWM_OFFSET_UCM_RDMA_CQ_CONS_32BIT);
	uresp.icid = cq->icid;

	rc = ib_copy_to_udata(udata, &uresp, sizeof(uresp));

	if (rc) {
		QL_DPRINT12(ha, "ib_copy_to_udata error cqid=0x%x[%d]\n",
			cq->icid, rc);
	}

	QL_DPRINT12(ha, "exit [%d]\n", rc);
	return rc;
}