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
struct vnode {scalar_t__ v_type; scalar_t__ v_usecount; } ;
typedef  enum vgetstate { ____Placeholder_vgetstate } vgetstate ;

/* Variables and functions */
 scalar_t__ VCHR ; 
 int VGET_HOLDCNT ; 
 int VGET_USECOUNT ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  _vhold (struct vnode*,int) ; 
 int /*<<< orphan*/  refcount_acquire (scalar_t__*) ; 
 scalar_t__ refcount_acquire_if_not_zero (scalar_t__*) ; 
 int /*<<< orphan*/  v_incr_devcount (struct vnode*) ; 
 int /*<<< orphan*/  vholdl (struct vnode*) ; 

__attribute__((used)) static enum vgetstate
_vget_prep(struct vnode *vp, bool interlock)
{
	enum vgetstate vs;

	if (__predict_true(vp->v_type != VCHR)) {
		if (refcount_acquire_if_not_zero(&vp->v_usecount)) {
			vs = VGET_USECOUNT;
		} else {
			_vhold(vp, interlock);
			vs = VGET_HOLDCNT;
		}
	} else {
		if (!interlock)
			VI_LOCK(vp);
		if (vp->v_usecount == 0) {
			vholdl(vp);
			vs = VGET_HOLDCNT;
		} else {
			v_incr_devcount(vp);
			refcount_acquire(&vp->v_usecount);
			vs = VGET_USECOUNT;
		}
		if (!interlock)
			VI_UNLOCK(vp);
	}
	return (vs);
}