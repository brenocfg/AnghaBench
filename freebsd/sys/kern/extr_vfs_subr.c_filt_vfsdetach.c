#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {TYPE_2__* v_pollinfo; } ;
struct knote {scalar_t__ kn_hook; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {TYPE_1__ vpi_selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 

__attribute__((used)) static void
filt_vfsdetach(struct knote *kn)
{
	struct vnode *vp = (struct vnode *)kn->kn_hook;

	KASSERT(vp->v_pollinfo != NULL, ("Missing v_pollinfo"));
	knlist_remove(&vp->v_pollinfo->vpi_selinfo.si_note, kn, 0);
	vdrop(vp);
}