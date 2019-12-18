#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct thread {TYPE_2__* td_proc; } ;
struct flock {void* l_type; scalar_t__ l_len; scalar_t__ l_start; void* l_whence; } ;
struct filedesc_to_leader {scalar_t__ fdl_holdcount; scalar_t__ fdl_wakeup; TYPE_3__* fdl_leader; struct filedesc_to_leader* fdl_next; } ;
struct filedesc {int dummy; } ;
struct file {scalar_t__ f_type; struct vnode* f_vnode; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int p_flag; } ;
struct TYPE_5__ {struct filedesc_to_leader* p_fdtol; struct filedesc* p_fd; TYPE_1__* p_leader; } ;
struct TYPE_4__ {int p_flag; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  F_POSIX ; 
 void* F_UNLCK ; 
 int P_ADVLOCK ; 
 void* SEEK_SET ; 
 int /*<<< orphan*/  VOP_ADVLOCK (struct vnode*,int /*<<< orphan*/ ,void*,struct flock*,int /*<<< orphan*/ ) ; 
 int fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  wakeup (struct filedesc_to_leader*) ; 

int
closef(struct file *fp, struct thread *td)
{
	struct vnode *vp;
	struct flock lf;
	struct filedesc_to_leader *fdtol;
	struct filedesc *fdp;

	/*
	 * POSIX record locking dictates that any close releases ALL
	 * locks owned by this process.  This is handled by setting
	 * a flag in the unlock to free ONLY locks obeying POSIX
	 * semantics, and not to free BSD-style file locks.
	 * If the descriptor was in a message, POSIX-style locks
	 * aren't passed with the descriptor, and the thread pointer
	 * will be NULL.  Callers should be careful only to pass a
	 * NULL thread pointer when there really is no owning
	 * context that might have locks, or the locks will be
	 * leaked.
	 */
	if (fp->f_type == DTYPE_VNODE && td != NULL) {
		vp = fp->f_vnode;
		if ((td->td_proc->p_leader->p_flag & P_ADVLOCK) != 0) {
			lf.l_whence = SEEK_SET;
			lf.l_start = 0;
			lf.l_len = 0;
			lf.l_type = F_UNLCK;
			(void) VOP_ADVLOCK(vp, (caddr_t)td->td_proc->p_leader,
			    F_UNLCK, &lf, F_POSIX);
		}
		fdtol = td->td_proc->p_fdtol;
		if (fdtol != NULL) {
			/*
			 * Handle special case where file descriptor table is
			 * shared between multiple process leaders.
			 */
			fdp = td->td_proc->p_fd;
			FILEDESC_XLOCK(fdp);
			for (fdtol = fdtol->fdl_next;
			    fdtol != td->td_proc->p_fdtol;
			    fdtol = fdtol->fdl_next) {
				if ((fdtol->fdl_leader->p_flag &
				    P_ADVLOCK) == 0)
					continue;
				fdtol->fdl_holdcount++;
				FILEDESC_XUNLOCK(fdp);
				lf.l_whence = SEEK_SET;
				lf.l_start = 0;
				lf.l_len = 0;
				lf.l_type = F_UNLCK;
				vp = fp->f_vnode;
				(void) VOP_ADVLOCK(vp,
				    (caddr_t)fdtol->fdl_leader, F_UNLCK, &lf,
				    F_POSIX);
				FILEDESC_XLOCK(fdp);
				fdtol->fdl_holdcount--;
				if (fdtol->fdl_holdcount == 0 &&
				    fdtol->fdl_wakeup != 0) {
					fdtol->fdl_wakeup = 0;
					wakeup(fdtol);
				}
			}
			FILEDESC_XUNLOCK(fdp);
		}
	}
	return (fdrop(fp, td));
}