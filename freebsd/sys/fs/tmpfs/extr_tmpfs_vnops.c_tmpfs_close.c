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
struct vop_close_args {struct vnode* a_vp; } ;
struct vnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tmpfs_update (struct vnode*) ; 

__attribute__((used)) static int
tmpfs_close(struct vop_close_args *v)
{
	struct vnode *vp = v->a_vp;

	/* Update node times. */
	tmpfs_update(vp);

	return (0);
}