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
struct vnode {int v_vflag; } ;
struct file {scalar_t__ f_type; struct vnode* f_vnode; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int VV_PROCDEP ; 

__attribute__((used)) static bool
is_unsafe(struct file *fp)
{
	struct vnode *vp;

	if (fp->f_type != DTYPE_VNODE)
		return (false);

	vp = fp->f_vnode;
	return ((vp->v_vflag & VV_PROCDEP) != 0);
}