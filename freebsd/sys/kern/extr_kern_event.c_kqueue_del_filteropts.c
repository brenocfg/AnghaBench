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
struct TYPE_2__ {scalar_t__ for_refcnt; int /*<<< orphan*/ * for_fop; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ EVFILT_SYSCOUNT ; 
 int /*<<< orphan*/  filterops_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null_filtops ; 
 TYPE_1__* sysfilt_ops ; 

int
kqueue_del_filteropts(int filt)
{
	int error;

	error = 0;
	if (filt > 0 || filt + EVFILT_SYSCOUNT < 0)
		return EINVAL;

	mtx_lock(&filterops_lock);
	if (sysfilt_ops[~filt].for_fop == &null_filtops ||
	    sysfilt_ops[~filt].for_fop == NULL)
		error = EINVAL;
	else if (sysfilt_ops[~filt].for_refcnt != 0)
		error = EBUSY;
	else {
		sysfilt_ops[~filt].for_fop = &null_filtops;
		sysfilt_ops[~filt].for_refcnt = 0;
	}
	mtx_unlock(&filterops_lock);

	return error;
}