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
struct thread {int dummy; } ;
typedef  enum vgetstate { ____Placeholder_vgetstate } vgetstate ;

/* Variables and functions */
 int LK_INTERLOCK ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int _vget_prep (struct vnode*,int) ; 
 struct thread* curthread ; 
 int vget_finish (struct vnode*,int,int) ; 

int
vget(struct vnode *vp, int flags, struct thread *td)
{
	enum vgetstate vs;

	MPASS(td == curthread);

	vs = _vget_prep(vp, (flags & LK_INTERLOCK) != 0);
	return (vget_finish(vp, flags, vs));
}