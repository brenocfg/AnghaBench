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
struct ib_qp {int /*<<< orphan*/  usecnt; TYPE_1__* device; } ;
struct ib_flow {struct ib_qp* qp; } ;
struct TYPE_2__ {int (* destroy_flow ) (struct ib_flow*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_flow*) ; 

int ib_destroy_flow(struct ib_flow *flow_id)
{
	int err;
	struct ib_qp *qp = flow_id->qp;

	err = qp->device->destroy_flow(flow_id);
	if (!err)
		atomic_dec(&qp->usecnt);
	return err;
}