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
struct qlnxr_qp {int dummy; } ;
struct qlnxr_dev {int gsi_qp_created; int /*<<< orphan*/  ha; struct qlnxr_qp* gsi_qp; void* gsi_rqcq; void* gsi_sqcq; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*) ; 
 void* get_qlnxr_cq (int /*<<< orphan*/ ) ; 

void
qlnxr_store_gsi_qp_cq(struct qlnxr_dev *dev,
		struct qlnxr_qp *qp,
		struct ib_qp_init_attr *attrs)
{
	QL_DPRINT12(dev->ha, "enter\n");
		
	dev->gsi_qp_created = 1;
	dev->gsi_sqcq = get_qlnxr_cq((attrs->send_cq));
	dev->gsi_rqcq = get_qlnxr_cq((attrs->recv_cq));
	dev->gsi_qp = qp;

	QL_DPRINT12(dev->ha, "exit\n");

	return;
}