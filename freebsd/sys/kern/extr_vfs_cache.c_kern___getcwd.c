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
struct filedesc {struct vnode* fd_rdir; struct vnode* fd_cdir; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 scalar_t__ KTRPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_NAMEI ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int UIO_SYSSPACE ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,scalar_t__) ; 
 int copyout (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  curthread ; 
 int disablecwd ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrnamei (char*) ; 
 char* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int vn_fullpath1 (struct thread*,struct vnode*,struct vnode*,char*,char**,size_t) ; 
 int /*<<< orphan*/  vrefact (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
kern___getcwd(struct thread *td, char *buf, enum uio_seg bufseg, size_t buflen,
    size_t path_max)
{
	char *bp, *tmpbuf;
	struct filedesc *fdp;
	struct vnode *cdir, *rdir;
	int error;

	if (__predict_false(disablecwd))
		return (ENODEV);
	if (__predict_false(buflen < 2))
		return (EINVAL);
	if (buflen > path_max)
		buflen = path_max;

	tmpbuf = malloc(buflen, M_TEMP, M_WAITOK);
	fdp = td->td_proc->p_fd;
	FILEDESC_SLOCK(fdp);
	cdir = fdp->fd_cdir;
	vrefact(cdir);
	rdir = fdp->fd_rdir;
	vrefact(rdir);
	FILEDESC_SUNLOCK(fdp);
	error = vn_fullpath1(td, cdir, rdir, tmpbuf, &bp, buflen);
	vrele(rdir);
	vrele(cdir);

	if (!error) {
		if (bufseg == UIO_SYSSPACE)
			bcopy(bp, buf, strlen(bp) + 1);
		else
			error = copyout(bp, buf, strlen(bp) + 1);
#ifdef KTRACE
	if (KTRPOINT(curthread, KTR_NAMEI))
		ktrnamei(bp);
#endif
	}
	free(tmpbuf, M_TEMP);
	return (error);
}