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
struct vop_kqfilter_args {struct knote* a_kn; struct vnode* a_vp; } ;
struct vnode {TYPE_2__* v_pollinfo; } ;
struct knote {int kn_filter; scalar_t__ kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct knlist {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {struct knlist si_note; } ;
struct TYPE_4__ {TYPE_1__ vpi_selinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  EVFILT_READ 130 
#define  EVFILT_VNODE 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  knlist_add (struct knlist*,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_addpollinfo (struct vnode*) ; 
 int /*<<< orphan*/  vfsread_filtops ; 
 int /*<<< orphan*/  vfsvnode_filtops ; 
 int /*<<< orphan*/  vfswrite_filtops ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 

int
vfs_kqfilter(struct vop_kqfilter_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct knote *kn = ap->a_kn;
	struct knlist *knl;

	switch (kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &vfsread_filtops;
		break;
	case EVFILT_WRITE:
		kn->kn_fop = &vfswrite_filtops;
		break;
	case EVFILT_VNODE:
		kn->kn_fop = &vfsvnode_filtops;
		break;
	default:
		return (EINVAL);
	}

	kn->kn_hook = (caddr_t)vp;

	v_addpollinfo(vp);
	if (vp->v_pollinfo == NULL)
		return (ENOMEM);
	knl = &vp->v_pollinfo->vpi_selinfo.si_note;
	vhold(vp);
	knlist_add(knl, kn, 0);

	return (0);
}