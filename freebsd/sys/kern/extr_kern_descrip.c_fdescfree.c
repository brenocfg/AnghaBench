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
struct thread {struct proc* td_proc; } ;
struct proc {struct filedesc* p_fd; int /*<<< orphan*/ * p_fdtol; } ;
struct filedesc {struct vnode* fd_jdir; struct vnode* fd_rdir; struct vnode* fd_cdir; int /*<<< orphan*/  fd_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ RACCT_ENABLED () ; 
 int /*<<< orphan*/  RACCT_NOFILE ; 
 int /*<<< orphan*/  fdclearlocks (struct thread*) ; 
 int /*<<< orphan*/  fdescfree_fds (struct thread*,struct filedesc*,int) ; 
 int /*<<< orphan*/  racct_set_unlocked (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

void
fdescfree(struct thread *td)
{
	struct proc *p;
	struct filedesc *fdp;
	struct vnode *cdir, *jdir, *rdir;

	p = td->td_proc;
	fdp = p->p_fd;
	MPASS(fdp != NULL);

#ifdef RACCT
	if (RACCT_ENABLED())
		racct_set_unlocked(p, RACCT_NOFILE, 0);
#endif

	if (p->p_fdtol != NULL)
		fdclearlocks(td);

	PROC_LOCK(p);
	p->p_fd = NULL;
	PROC_UNLOCK(p);

	if (refcount_release(&fdp->fd_refcnt) == 0)
		return;

	FILEDESC_XLOCK(fdp);
	cdir = fdp->fd_cdir;
	fdp->fd_cdir = NULL;
	rdir = fdp->fd_rdir;
	fdp->fd_rdir = NULL;
	jdir = fdp->fd_jdir;
	fdp->fd_jdir = NULL;
	FILEDESC_XUNLOCK(fdp);

	if (cdir != NULL)
		vrele(cdir);
	if (rdir != NULL)
		vrele(rdir);
	if (jdir != NULL)
		vrele(jdir);

	fdescfree_fds(td, fdp, 1);
}