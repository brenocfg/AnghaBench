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
struct vnode {int /*<<< orphan*/ * v_label; } ;
struct ucred {int dummy; } ;
struct componentname {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  MAC_CHECK_PROBE4 (int /*<<< orphan*/ ,int,struct ucred*,struct vnode*,struct vnode*,struct componentname*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK (int /*<<< orphan*/ ,struct ucred*,struct vnode*,int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ *,int,struct componentname*) ; 
 int /*<<< orphan*/  vnode_check_rename_to ; 

int
mac_vnode_check_rename_to(struct ucred *cred, struct vnode *dvp,
    struct vnode *vp, int samedir, struct componentname *cnp)
{
	int error;

	ASSERT_VOP_LOCKED(dvp, "mac_vnode_check_rename_to");
	ASSERT_VOP_LOCKED(vp, "mac_vnode_check_rename_to");

	MAC_POLICY_CHECK(vnode_check_rename_to, cred, dvp, dvp->v_label, vp,
	    vp != NULL ? vp->v_label : NULL, samedir, cnp);
	MAC_CHECK_PROBE4(vnode_check_rename_to, error, cred, dvp, vp, cnp);
	return (error);
}