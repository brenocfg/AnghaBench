#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop_close_args {int a_fflag; struct thread* a_td; struct vnode* a_vp; } ;
struct vnode {int v_iflag; int /*<<< orphan*/ * v_data; struct cdev* v_rdev; } ;
struct thread {struct proc* td_proc; } ;
struct proc {TYPE_1__* p_session; } ;
struct cdevsw {int d_flags; int (* d_close ) (struct cdev*,int,int /*<<< orphan*/ ,struct thread*) ;} ;
struct cdev {scalar_t__ si_refcount; } ;
struct TYPE_3__ {int /*<<< orphan*/ * s_ttydp; struct vnode* s_ttyvp; } ;

/* Variables and functions */
 int D_TRACKCLOSE ; 
 int ENXIO ; 
 int FLASTCLOSE ; 
 int FNONBLOCK ; 
 int FREVOKE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SESS_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SESS_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VI_UNLOCK (struct vnode*) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int count_dev (struct cdev*) ; 
 struct cdevsw* dev_refthread (struct cdev*,int*) ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 int /*<<< orphan*/  devtoname (struct cdev*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int stub1 (struct cdev*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vholdl (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
devfs_close(struct vop_close_args *ap)
{
	struct vnode *vp = ap->a_vp, *oldvp;
	struct thread *td = ap->a_td;
	struct proc *p;
	struct cdev *dev = vp->v_rdev;
	struct cdevsw *dsw;
	int dflags, error, ref, vp_locked;

	/*
	 * XXX: Don't call d_close() if we were called because of
	 * XXX: insmntque1() failure.
	 */
	if (vp->v_data == NULL)
		return (0);

	/*
	 * Hack: a tty device that is a controlling terminal
	 * has a reference from the session structure.
	 * We cannot easily tell that a character device is
	 * a controlling terminal, unless it is the closing
	 * process' controlling terminal.  In that case,
	 * if the reference count is 2 (this last descriptor
	 * plus the session), release the reference from the session.
	 */
	if (td != NULL) {
		p = td->td_proc;
		PROC_LOCK(p);
		if (vp == p->p_session->s_ttyvp) {
			PROC_UNLOCK(p);
			oldvp = NULL;
			sx_xlock(&proctree_lock);
			if (vp == p->p_session->s_ttyvp) {
				SESS_LOCK(p->p_session);
				VI_LOCK(vp);
				if (count_dev(dev) == 2 &&
				    (vp->v_iflag & VI_DOOMED) == 0) {
					p->p_session->s_ttyvp = NULL;
					p->p_session->s_ttydp = NULL;
					oldvp = vp;
				}
				VI_UNLOCK(vp);
				SESS_UNLOCK(p->p_session);
			}
			sx_xunlock(&proctree_lock);
			if (oldvp != NULL)
				vrele(oldvp);
		} else
			PROC_UNLOCK(p);
	}
	/*
	 * We do not want to really close the device if it
	 * is still in use unless we are trying to close it
	 * forcibly. Since every use (buffer, vnode, swap, cmap)
	 * holds a reference to the vnode, and because we mark
	 * any other vnodes that alias this device, when the
	 * sum of the reference counts on all the aliased
	 * vnodes descends to one, we are on last close.
	 */
	dsw = dev_refthread(dev, &ref);
	if (dsw == NULL)
		return (ENXIO);
	dflags = 0;
	VI_LOCK(vp);
	if (vp->v_iflag & VI_DOOMED) {
		/* Forced close. */
		dflags |= FREVOKE | FNONBLOCK;
	} else if (dsw->d_flags & D_TRACKCLOSE) {
		/* Keep device updated on status. */
	} else if (count_dev(dev) > 1) {
		VI_UNLOCK(vp);
		dev_relthread(dev, ref);
		return (0);
	}
	if (count_dev(dev) == 1)
		dflags |= FLASTCLOSE;
	vholdl(vp);
	VI_UNLOCK(vp);
	vp_locked = VOP_ISLOCKED(vp);
	VOP_UNLOCK(vp, 0);
	KASSERT(dev->si_refcount > 0,
	    ("devfs_close() on un-referenced struct cdev *(%s)", devtoname(dev)));
	error = dsw->d_close(dev, ap->a_fflag | dflags, S_IFCHR, td);
	dev_relthread(dev, ref);
	vn_lock(vp, vp_locked | LK_RETRY);
	vdrop(vp);
	return (error);
}