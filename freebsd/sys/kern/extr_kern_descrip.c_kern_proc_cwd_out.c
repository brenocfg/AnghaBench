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
struct sbuf {int dummy; } ;
struct proc {int dummy; } ;
struct filedesc {int /*<<< orphan*/ * fd_cdir; } ;
struct export_fd_buf {int /*<<< orphan*/  remainder; struct sbuf* sb; struct filedesc* fdp; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  KF_FD_TYPE_CWD ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int export_vnode_to_sb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct export_fd_buf*) ; 
 int /*<<< orphan*/  fddrop (struct filedesc*) ; 
 struct filedesc* fdhold (struct proc*) ; 
 int /*<<< orphan*/  free (struct export_fd_buf*,int /*<<< orphan*/ ) ; 
 struct export_fd_buf* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrefact (int /*<<< orphan*/ *) ; 

int
kern_proc_cwd_out(struct proc *p,  struct sbuf *sb, ssize_t maxlen)
{
	struct filedesc *fdp;
	struct export_fd_buf *efbuf;
	int error;

	PROC_LOCK_ASSERT(p, MA_OWNED);

	fdp = fdhold(p);
	PROC_UNLOCK(p);
	if (fdp == NULL)
		return (EINVAL);

	efbuf = malloc(sizeof(*efbuf), M_TEMP, M_WAITOK);
	efbuf->fdp = fdp;
	efbuf->sb = sb;
	efbuf->remainder = maxlen;

	FILEDESC_SLOCK(fdp);
	if (fdp->fd_cdir == NULL)
		error = EINVAL;
	else {
		vrefact(fdp->fd_cdir);
		error = export_vnode_to_sb(fdp->fd_cdir, KF_FD_TYPE_CWD,
		    FREAD, efbuf);
	}
	FILEDESC_SUNLOCK(fdp);
	fddrop(fdp);
	free(efbuf, M_TEMP);
	return (error);
}