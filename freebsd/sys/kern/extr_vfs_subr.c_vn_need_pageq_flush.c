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
struct vnode {int v_vflag; struct vm_object* v_object; } ;
struct vm_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VI_MTX (struct vnode*) ; 
 int VV_NOSYNC ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_mightbedirty (struct vm_object*) ; 

int
vn_need_pageq_flush(struct vnode *vp)
{
	struct vm_object *obj;
	int need;

	MPASS(mtx_owned(VI_MTX(vp)));
	need = 0;
	if ((obj = vp->v_object) != NULL && (vp->v_vflag & VV_NOSYNC) == 0 &&
	    vm_object_mightbedirty(obj))
		need = 1;
	return (need);
}