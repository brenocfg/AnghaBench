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
struct uio {scalar_t__ uio_resid; int /*<<< orphan*/  uio_offset; struct thread* uio_td; int /*<<< orphan*/  uio_rw; } ;
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_ucred; } ;
struct file {scalar_t__ f_type; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 scalar_t__ DTYPE_SOCKET ; 
 int EINTR ; 
 int EPIPE ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_GENIO ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 struct uio* cloneuio (struct uio*) ; 
 int fo_write (struct file*,struct uio*,int /*<<< orphan*/ ,int,struct thread*) ; 
 int /*<<< orphan*/  ktrgenio (int,int /*<<< orphan*/ ,struct uio*,int) ; 
 int /*<<< orphan*/  tdsignal (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dofilewrite(struct thread *td, int fd, struct file *fp, struct uio *auio,
    off_t offset, int flags)
{
	ssize_t cnt;
	int error;
#ifdef KTRACE
	struct uio *ktruio = NULL;
#endif

	AUDIT_ARG_FD(fd);
	auio->uio_rw = UIO_WRITE;
	auio->uio_td = td;
	auio->uio_offset = offset;
#ifdef KTRACE
	if (KTRPOINT(td, KTR_GENIO))
		ktruio = cloneuio(auio);
#endif
	cnt = auio->uio_resid;
	if ((error = fo_write(fp, auio, td->td_ucred, flags, td))) {
		if (auio->uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
		/* Socket layer is responsible for issuing SIGPIPE. */
		if (fp->f_type != DTYPE_SOCKET && error == EPIPE) {
			PROC_LOCK(td->td_proc);
			tdsignal(td, SIGPIPE);
			PROC_UNLOCK(td->td_proc);
		}
	}
	cnt -= auio->uio_resid;
#ifdef KTRACE
	if (ktruio != NULL) {
		ktruio->uio_resid = cnt;
		ktrgenio(fd, UIO_WRITE, ktruio, error);
	}
#endif
	td->td_retval[0] = cnt;
	return (error);
}