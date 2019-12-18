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
struct vop_readlink_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_uio; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VLNK ; 
 int ncl_bioread (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_readlink(struct vop_readlink_args *ap)
{
	struct vnode *vp = ap->a_vp;

	if (vp->v_type != VLNK)
		return (EINVAL);
	return (ncl_bioread(vp, ap->a_uio, 0, ap->a_cred));
}