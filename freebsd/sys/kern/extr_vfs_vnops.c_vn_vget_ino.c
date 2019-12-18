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
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  vn_get_ino_alloc_vget ; 
 int vn_vget_ino_gen (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct vnode**) ; 

int
vn_vget_ino(struct vnode *vp, ino_t ino, int lkflags, struct vnode **rvp)
{

	return (vn_vget_ino_gen(vp, vn_get_ino_alloc_vget, &ino,
	    lkflags, rvp));
}