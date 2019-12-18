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
struct vnode {int /*<<< orphan*/  v_label; } ;
struct ucred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  MAC_CHECK_PROBE3 (int /*<<< orphan*/ ,int,struct ucred*,struct vnode*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK (int /*<<< orphan*/ ,struct ucred*,struct vnode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnode_check_listextattr ; 

int
mac_vnode_check_listextattr(struct ucred *cred, struct vnode *vp,
    int attrnamespace)
{
	int error;

	ASSERT_VOP_LOCKED(vp, "mac_vnode_check_listextattr");

	MAC_POLICY_CHECK(vnode_check_listextattr, cred, vp, vp->v_label,
	    attrnamespace);
	MAC_CHECK_PROBE3(vnode_check_listextattr, error, cred, vp,
	    attrnamespace);

	return (error);
}