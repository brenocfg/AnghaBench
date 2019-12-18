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
 int /*<<< orphan*/  MAC_CHECK_PROBE4 (int /*<<< orphan*/ ,int,struct ucred*,struct vnode*,int,char const*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK (int /*<<< orphan*/ ,struct ucred*,struct vnode*,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  vnode_check_getextattr ; 

int
mac_vnode_check_getextattr(struct ucred *cred, struct vnode *vp,
    int attrnamespace, const char *name)
{
	int error;

	ASSERT_VOP_LOCKED(vp, "mac_vnode_check_getextattr");

	MAC_POLICY_CHECK(vnode_check_getextattr, cred, vp, vp->v_label,
	    attrnamespace, name);
	MAC_CHECK_PROBE4(vnode_check_getextattr, error, cred, vp,
	    attrnamespace, name);

	return (error);
}