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
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ROOTINO ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int VFS_VGET (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**) ; 

__attribute__((used)) static int
ext2_root(struct mount *mp, int flags, struct vnode **vpp)
{
	struct vnode *nvp;
	int error;

	error = VFS_VGET(mp, EXT2_ROOTINO, LK_EXCLUSIVE, &nvp);
	if (error)
		return (error);
	*vpp = nvp;
	return (0);
}