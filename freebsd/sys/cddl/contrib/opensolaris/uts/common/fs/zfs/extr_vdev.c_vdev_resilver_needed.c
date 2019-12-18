#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ vdev_children; struct TYPE_6__** vdev_child; int /*<<< orphan*/  vdev_dtl_lock; int /*<<< orphan*/ * vdev_dtl; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 size_t DTL_MISSING ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_dtl_max (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_dtl_min (TYPE_1__*) ; 
 scalar_t__ vdev_writeable (TYPE_1__*) ; 

boolean_t
vdev_resilver_needed(vdev_t *vd, uint64_t *minp, uint64_t *maxp)
{
	boolean_t needed = B_FALSE;
	uint64_t thismin = UINT64_MAX;
	uint64_t thismax = 0;

	if (vd->vdev_children == 0) {
		mutex_enter(&vd->vdev_dtl_lock);
		if (!range_tree_is_empty(vd->vdev_dtl[DTL_MISSING]) &&
		    vdev_writeable(vd)) {

			thismin = vdev_dtl_min(vd);
			thismax = vdev_dtl_max(vd);
			needed = B_TRUE;
		}
		mutex_exit(&vd->vdev_dtl_lock);
	} else {
		for (int c = 0; c < vd->vdev_children; c++) {
			vdev_t *cvd = vd->vdev_child[c];
			uint64_t cmin, cmax;

			if (vdev_resilver_needed(cvd, &cmin, &cmax)) {
				thismin = MIN(thismin, cmin);
				thismax = MAX(thismax, cmax);
				needed = B_TRUE;
			}
		}
	}

	if (needed && minp) {
		*minp = thismin;
		*maxp = thismax;
	}
	return (needed);
}