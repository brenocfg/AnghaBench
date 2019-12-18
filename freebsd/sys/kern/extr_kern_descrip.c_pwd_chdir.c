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
struct vnode {scalar_t__ v_usecount; } ;
struct thread {TYPE_1__* td_proc; } ;
struct filedesc {struct vnode* fd_cdir; } ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  VNASSERT (int,struct vnode*,char*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

void
pwd_chdir(struct thread *td, struct vnode *vp)
{
	struct filedesc *fdp;
	struct vnode *oldvp;

	fdp = td->td_proc->p_fd;
	FILEDESC_XLOCK(fdp);
	VNASSERT(vp->v_usecount > 0, vp,
	    ("chdir to a vnode with zero usecount"));
	oldvp = fdp->fd_cdir;
	fdp->fd_cdir = vp;
	FILEDESC_XUNLOCK(fdp);
	vrele(oldvp);
}