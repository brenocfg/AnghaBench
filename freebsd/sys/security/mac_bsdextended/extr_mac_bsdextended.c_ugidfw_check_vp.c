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
struct vnode {int dummy; } ;
struct vattr {int dummy; } ;
struct ucred {int dummy; } ;

/* Variables and functions */
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int ugidfw_check (struct ucred*,struct vnode*,struct vattr*,int) ; 
 int /*<<< orphan*/  ugidfw_enabled ; 

int
ugidfw_check_vp(struct ucred *cred, struct vnode *vp, int acc_mode)
{
	int error;
	struct vattr vap;

	if (!ugidfw_enabled)
		return (0);
	error = VOP_GETATTR(vp, &vap, cred);
	if (error)
		return (error);
	return (ugidfw_check(cred, vp, &vap, acc_mode));
}