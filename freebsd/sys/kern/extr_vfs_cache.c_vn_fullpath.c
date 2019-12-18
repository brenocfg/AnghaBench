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
struct vnode {int dummy; } ;
struct thread {TYPE_1__* td_proc; } ;
struct filedesc {struct vnode* fd_rdir; } ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disablefullpath ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vn_fullpath1 (struct thread*,struct vnode*,struct vnode*,char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrefact (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
vn_fullpath(struct thread *td, struct vnode *vn, char **retbuf, char **freebuf)
{
	char *buf;
	struct filedesc *fdp;
	struct vnode *rdir;
	int error;

	if (__predict_false(disablefullpath))
		return (ENODEV);
	if (__predict_false(vn == NULL))
		return (EINVAL);

	buf = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
	fdp = td->td_proc->p_fd;
	FILEDESC_SLOCK(fdp);
	rdir = fdp->fd_rdir;
	vrefact(rdir);
	FILEDESC_SUNLOCK(fdp);
	error = vn_fullpath1(td, vn, rdir, buf, retbuf, MAXPATHLEN);
	vrele(rdir);

	if (!error)
		*freebuf = buf;
	else
		free(buf, M_TEMP);
	return (error);
}