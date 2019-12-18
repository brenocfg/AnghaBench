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

/* Variables and functions */
#define  LK_DOWNGRADE 131 
#define  LK_EXCLUSIVE 130 
 int LK_RELEASE ; 
#define  LK_SHARED 129 
 int LK_TYPE_MASK ; 
#define  LK_UPGRADE 128 
 int VOP_ISLOCKED (struct vnode*) ; 

__attribute__((used)) static int
unionfs_get_llt_revlock(struct vnode *vp, int flags)
{
	int revlock;

	revlock = 0;

	switch (flags & LK_TYPE_MASK) {
	case LK_SHARED:
		if (VOP_ISLOCKED(vp) == LK_EXCLUSIVE)
			revlock = LK_UPGRADE;
		else
			revlock = LK_RELEASE;
		break;
	case LK_EXCLUSIVE:
	case LK_UPGRADE:
		revlock = LK_RELEASE;
		break;
	case LK_DOWNGRADE:
		revlock = LK_UPGRADE;
		break;
	default:
		break;
	}

	return (revlock);
}