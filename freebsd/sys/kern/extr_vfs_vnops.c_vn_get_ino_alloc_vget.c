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
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int VFS_VGET (struct mount*,int /*<<< orphan*/ ,int,struct vnode**) ; 

__attribute__((used)) static int
vn_get_ino_alloc_vget(struct mount *mp, void *arg, int lkflags,
    struct vnode **rvp)
{

	return (VFS_VGET(mp, *(ino_t *)arg, lkflags, rvp));
}