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
struct ib_xrcd {int /*<<< orphan*/  usecnt; int /*<<< orphan*/  tgt_qp_mutex; } ;
struct ib_qp {int /*<<< orphan*/  xrcd_list; int /*<<< orphan*/  usecnt; struct ib_xrcd* xrcd; struct ib_qp* real_qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ib_insert_xrcd_qp (struct ib_xrcd*,struct ib_qp*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_close_qp (struct ib_qp*) ; 
 int ib_destroy_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ib_destroy_shared_qp(struct ib_qp *qp)
{
	struct ib_xrcd *xrcd;
	struct ib_qp *real_qp;
	int ret;

	real_qp = qp->real_qp;
	xrcd = real_qp->xrcd;

	mutex_lock(&xrcd->tgt_qp_mutex);
	ib_close_qp(qp);
	if (atomic_read(&real_qp->usecnt) == 0)
		list_del(&real_qp->xrcd_list);
	else
		real_qp = NULL;
	mutex_unlock(&xrcd->tgt_qp_mutex);

	if (real_qp) {
		ret = ib_destroy_qp(real_qp);
		if (!ret)
			atomic_dec(&xrcd->usecnt);
		else
			__ib_insert_xrcd_qp(xrcd, real_qp);
	}

	return 0;
}