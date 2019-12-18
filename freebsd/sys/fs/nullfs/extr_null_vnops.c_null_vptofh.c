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
struct vop_vptofh_args {int /*<<< orphan*/  a_fhp; int /*<<< orphan*/  a_vp; } ;
struct vnode {int dummy; } ;

/* Variables and functions */
 struct vnode* NULLVPTOLOWERVP (int /*<<< orphan*/ ) ; 
 int VOP_VPTOFH (struct vnode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
null_vptofh(struct vop_vptofh_args *ap)
{
	struct vnode *lvp;

	lvp = NULLVPTOLOWERVP(ap->a_vp);
	return VOP_VPTOFH(lvp, ap->a_fhp);
}