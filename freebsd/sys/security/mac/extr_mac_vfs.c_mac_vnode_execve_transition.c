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
struct label {int dummy; } ;
struct image_params {int /*<<< orphan*/  execlabel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM (int /*<<< orphan*/ ,struct ucred*,struct ucred*,struct vnode*,int /*<<< orphan*/ ,struct label*,struct image_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_execve_transition ; 

void
mac_vnode_execve_transition(struct ucred *old, struct ucred *new,
    struct vnode *vp, struct label *interpvplabel, struct image_params *imgp)
{

	ASSERT_VOP_LOCKED(vp, "mac_vnode_execve_transition");

	MAC_POLICY_PERFORM(vnode_execve_transition, old, new, vp,
	    vp->v_label, interpvplabel, imgp, imgp->execlabel);
}