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
struct vnode {TYPE_1__* v_pollinfo; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int vpi_revents; int vpi_events; int /*<<< orphan*/  vpi_lock; int /*<<< orphan*/  vpi_selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_addpollinfo (struct vnode*) ; 

int
vn_pollrecord(struct vnode *vp, struct thread *td, int events)
{

	v_addpollinfo(vp);
	mtx_lock(&vp->v_pollinfo->vpi_lock);
	if (vp->v_pollinfo->vpi_revents & events) {
		/*
		 * This leaves events we are not interested
		 * in available for the other process which
		 * which presumably had requested them
		 * (otherwise they would never have been
		 * recorded).
		 */
		events &= vp->v_pollinfo->vpi_revents;
		vp->v_pollinfo->vpi_revents &= ~events;

		mtx_unlock(&vp->v_pollinfo->vpi_lock);
		return (events);
	}
	vp->v_pollinfo->vpi_events |= events;
	selrecord(td, &vp->v_pollinfo->vpi_selinfo);
	mtx_unlock(&vp->v_pollinfo->vpi_lock);
	return (0);
}