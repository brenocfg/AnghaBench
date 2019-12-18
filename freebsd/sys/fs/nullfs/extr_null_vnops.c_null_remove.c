#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vop_remove_args {int /*<<< orphan*/  a_gen; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  null_flags; } ;

/* Variables and functions */
 struct vnode* NULLVPTOLOWERVP (struct vnode*) ; 
 int /*<<< orphan*/  NULLV_DROP ; 
 int /*<<< orphan*/  VREF (struct vnode*) ; 
 TYPE_1__* VTONULL (struct vnode*) ; 
 int null_bypass (int /*<<< orphan*/ *) ; 
 int vrefcnt (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
null_remove(struct vop_remove_args *ap)
{
	int retval, vreleit;
	struct vnode *lvp, *vp;

	vp = ap->a_vp;
	if (vrefcnt(vp) > 1) {
		lvp = NULLVPTOLOWERVP(vp);
		VREF(lvp);
		vreleit = 1;
	} else
		vreleit = 0;
	VTONULL(vp)->null_flags |= NULLV_DROP;
	retval = null_bypass(&ap->a_gen);
	if (vreleit != 0)
		vrele(lvp);
	return (retval);
}