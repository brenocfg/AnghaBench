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
struct acl {int dummy; } ;
typedef  int /*<<< orphan*/  acl_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  MAC_CHECK_PROBE4 (int /*<<< orphan*/ ,int,struct ucred*,struct vnode*,int /*<<< orphan*/ ,struct acl*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK (int /*<<< orphan*/ ,struct ucred*,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acl*) ; 
 int /*<<< orphan*/  vnode_check_setacl ; 

int
mac_vnode_check_setacl(struct ucred *cred, struct vnode *vp, acl_type_t type,
    struct acl *acl)
{
	int error;

	ASSERT_VOP_LOCKED(vp, "mac_vnode_check_setacl");

	MAC_POLICY_CHECK(vnode_check_setacl, cred, vp, vp->v_label, type, acl);
	MAC_CHECK_PROBE4(vnode_check_setacl, error, cred, vp, type, acl);

	return (error);
}