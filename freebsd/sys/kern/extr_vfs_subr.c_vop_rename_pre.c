#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vop_rename_args {TYPE_1__* a_tvp; TYPE_1__* a_tdvp; TYPE_1__* a_fvp; TYPE_1__* a_fdvp; } ;
struct TYPE_5__ {scalar_t__ v_vnlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VI_UNLOCKED (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ASSERT_VOP_UNLOCKED (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vhold (TYPE_1__*) ; 

void
vop_rename_pre(void *ap)
{
	struct vop_rename_args *a = ap;

#ifdef DEBUG_VFS_LOCKS
	if (a->a_tvp)
		ASSERT_VI_UNLOCKED(a->a_tvp, "VOP_RENAME");
	ASSERT_VI_UNLOCKED(a->a_tdvp, "VOP_RENAME");
	ASSERT_VI_UNLOCKED(a->a_fvp, "VOP_RENAME");
	ASSERT_VI_UNLOCKED(a->a_fdvp, "VOP_RENAME");

	/* Check the source (from). */
	if (a->a_tdvp->v_vnlock != a->a_fdvp->v_vnlock &&
	    (a->a_tvp == NULL || a->a_tvp->v_vnlock != a->a_fdvp->v_vnlock))
		ASSERT_VOP_UNLOCKED(a->a_fdvp, "vop_rename: fdvp locked");
	if (a->a_tvp == NULL || a->a_tvp->v_vnlock != a->a_fvp->v_vnlock)
		ASSERT_VOP_UNLOCKED(a->a_fvp, "vop_rename: fvp locked");

	/* Check the target. */
	if (a->a_tvp)
		ASSERT_VOP_LOCKED(a->a_tvp, "vop_rename: tvp not locked");
	ASSERT_VOP_LOCKED(a->a_tdvp, "vop_rename: tdvp not locked");
#endif
	if (a->a_tdvp != a->a_fdvp)
		vhold(a->a_fdvp);
	if (a->a_tvp != a->a_fvp)
		vhold(a->a_fvp);
	vhold(a->a_tdvp);
	if (a->a_tvp)
		vhold(a->a_tvp);
}