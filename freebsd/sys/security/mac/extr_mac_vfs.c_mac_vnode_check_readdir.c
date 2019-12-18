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
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct ucred*,struct vnode*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK (int /*<<< orphan*/ ,struct ucred*,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_check_readdir ; 

int
mac_vnode_check_readdir(struct ucred *cred, struct vnode *dvp)
{
	int error;

	ASSERT_VOP_LOCKED(dvp, "mac_vnode_check_readdir");

	MAC_POLICY_CHECK(vnode_check_readdir, cred, dvp, dvp->v_label);
	MAC_CHECK_PROBE2(vnode_check_readdir, error, cred, dvp);

	return (error);
}