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
struct uio {scalar_t__ uio_resid; struct thread* uio_td; int /*<<< orphan*/  uio_offset; int /*<<< orphan*/  uio_rw; } ;
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct file {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int EINTR ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_GENIO ; 
 int /*<<< orphan*/  UIO_READ ; 
 struct uio* cloneuio (struct uio*) ; 
 int fo_read (struct file*,struct uio*,int /*<<< orphan*/ ,int,struct thread*) ; 
 int /*<<< orphan*/  ktrgenio (int,int /*<<< orphan*/ ,struct uio*,int) ; 

__attribute__((used)) static int
dofileread(struct thread *td, int fd, struct file *fp, struct uio *auio,
    off_t offset, int flags)
{
	ssize_t cnt;
	int error;
#ifdef KTRACE
	struct uio *ktruio = NULL;
#endif

	AUDIT_ARG_FD(fd);

	/* Finish zero length reads right here */
	if (auio->uio_resid == 0) {
		td->td_retval[0] = 0;
		return (0);
	}
	auio->uio_rw = UIO_READ;
	auio->uio_offset = offset;
	auio->uio_td = td;
#ifdef KTRACE
	if (KTRPOINT(td, KTR_GENIO)) 
		ktruio = cloneuio(auio);
#endif
	cnt = auio->uio_resid;
	if ((error = fo_read(fp, auio, td->td_ucred, flags, td))) {
		if (auio->uio_resid != cnt && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
	}
	cnt -= auio->uio_resid;
#ifdef KTRACE
	if (ktruio != NULL) {
		ktruio->uio_resid = cnt;
		ktrgenio(fd, UIO_READ, ktruio, error);
	}
#endif
	td->td_retval[0] = cnt;
	return (error);
}