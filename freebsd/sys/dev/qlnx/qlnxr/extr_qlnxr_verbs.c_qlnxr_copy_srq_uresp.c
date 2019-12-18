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
struct qlnxr_srq {int /*<<< orphan*/  srq_id; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct qlnxr_create_srq_uresp {int /*<<< orphan*/  srq_id; } ;
struct ib_udata {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int ib_copy_to_udata (struct ib_udata*,struct qlnxr_create_srq_uresp*,int) ; 
 int /*<<< orphan*/  memset (struct qlnxr_create_srq_uresp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qlnxr_copy_srq_uresp(struct qlnxr_dev *dev,
	struct qlnxr_srq *srq,
	struct ib_udata *udata)
{
	struct qlnxr_create_srq_uresp	uresp;
	qlnx_host_t			*ha;
	int				rc;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	memset(&uresp, 0, sizeof(uresp));

	uresp.srq_id = srq->srq_id;

	rc = ib_copy_to_udata(udata, &uresp, sizeof(uresp));

	QL_DPRINT12(ha, "exit [%d]\n", rc);
	return rc;
}