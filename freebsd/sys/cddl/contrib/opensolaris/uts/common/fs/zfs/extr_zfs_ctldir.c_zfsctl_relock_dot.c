#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int v_iflag; } ;
typedef  TYPE_1__ vnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int LK_DOWNGRADE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_UPGRADE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int VOP_ISLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  vn_lock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vref (TYPE_1__*) ; 
 int /*<<< orphan*/  vrele (TYPE_1__*) ; 

int
zfsctl_relock_dot(vnode_t *dvp, int ltype)
{
	vref(dvp);
	if (ltype != VOP_ISLOCKED(dvp)) {
		if (ltype == LK_EXCLUSIVE)
			vn_lock(dvp, LK_UPGRADE | LK_RETRY);
		else /* if (ltype == LK_SHARED) */
			vn_lock(dvp, LK_DOWNGRADE | LK_RETRY);

		/* Relock for the "." case may left us with reclaimed vnode. */
		if ((dvp->v_iflag & VI_DOOMED) != 0) {
			vrele(dvp);
			return (SET_ERROR(ENOENT));
		}
	}
	return (0);
}